package com.github.mibs510;

import com.google.protobuf.InvalidProtocolBufferException;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousChannelGroup;
import java.nio.channels.AsynchronousSocketChannel;
import java.nio.channels.CompletionHandler;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.*;
import java.util.function.Consumer;

public class AsyncTCPClient {
    private AsynchronousSocketChannel clientChannel;
    private final ExecutorService executor = Executors.newCachedThreadPool();
    private final AsynchronousChannelGroup channelGroup;
    // Thread-safe queues for sending/receiving
    private final BlockingQueue<HmiClientMsgProto.HmiClientMessage> sendQueue = new LinkedBlockingQueue<>();
    private final Consumer<String> debugLogConsumer;
    private final Consumer<HmiServerMsgProto.HmiServerMsg> updateUiComponents;
    private final ByteBuffer readBuffer = ByteBuffer.allocate(256);

    public AsyncTCPClient(Consumer<String> debugLogConsumer,
                          Consumer<HmiServerMsgProto.HmiServerMsg> updateUiComponents)
            throws IOException {
        this.debugLogConsumer = debugLogConsumer;
        this.updateUiComponents = updateUiComponents;
        this.channelGroup = AsynchronousChannelGroup.withCachedThreadPool(executor, 1);
        this.clientChannel = AsynchronousSocketChannel.open(channelGroup);
    }

    public void connect(String host, int port) {
        clientChannel.connect(new InetSocketAddress(host, port), null, new CompletionHandler<Void, Void>() {
            @Override
            public void completed(Void result, Void attachment) {
                debugLogConsumer.accept("Connected to interface board.");
                startReading();
                startWriting(); // Start the writing process after connection
            }

            @Override
            public void failed(Throwable exc, Void attachment) {
                debugLogConsumer.accept("Connection failed: " + exc.getMessage());
                // Handle reconnection logic here if needed
            }
        });
    }

    public boolean sendMessage(HmiClientMsgProto.HmiClientMessage message) {
        return sendQueue.offer(message); // Add message to the queue
    }

    private void startReading() {
        clientChannel.read(readBuffer, null, new CompletionHandler<Integer, Void>() {
            @Override
            public void completed(Integer bytesRead, Void attachment) {
                if (bytesRead == -1) {
                    debugLogConsumer.accept("Interface board disconnected.");
                    closeChannel();
                    return;
                }
                readBuffer.flip();

                try {
                    HmiServerMsgProto.HmiServerMsg hmiServerMsg =
                            HmiServerMsgProto.HmiServerMsg.parseFrom(readBuffer);
                    if (hmiServerMsg.getPayloadCase() == HmiServerMsgProto.HmiServerMsg.PayloadCase.HMICLIENTMSG)
                        updateUiComponents.accept(hmiServerMsg);
                    else if (hmiServerMsg.getPayloadCase() ==
                            HmiServerMsgProto.HmiServerMsg.PayloadCase.HMISERVERRESPONSE)
                        debugLogConsumer.accept("Server response: " + hmiServerMsg.getHmiServerResponse().toString());
                    else if (hmiServerMsg.getPayloadCase() == HmiServerMsgProto.HmiServerMsg.PayloadCase.PAYLOAD_NOT_SET)
                        debugLogConsumer.accept("Received empty message from interface board.");
                } catch (InvalidProtocolBufferException e) {
                   debugLogConsumer.accept("Invalid message received from interface board. Bytes: " + bytesRead);
                }

                readBuffer.clear();
                // Continue reading in a loop
                clientChannel.read(readBuffer, null, this);
            }

            @Override
            public void failed(Throwable exc, Void attachment) {
                debugLogConsumer.accept("Read failed: " + exc.getMessage());
                closeChannel();
            }
        });
    }

    private void startWriting() {
        // Use a separate thread (or manage within CompletionHandler) to process the send queue
        executor.submit(() -> {
            try {
                while (!Thread.currentThread().isInterrupted()) {
                    HmiClientMsgProto.HmiClientMessage message = sendQueue.take(); // Block until a message is available
                    debugLogConsumer.accept("Sending message: " + message.toString());
                    ByteBuffer buffer = ByteBuffer.allocate(256);
                    ByteBuffer.wrap(message.toByteArray());
                    //ByteBuffer buffer = ByteBuffer.wrap(message.toByteArray());
                    byte[] messageBuffer = message.toByteArray();
                    clientChannel.write(buffer);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                debugLogConsumer.accept("Writer interrupted or failed: " + e.getMessage());
            }
        });
    }

    private void closeChannel() {
        try {
            if (clientChannel != null && clientChannel.isOpen()) {
                clientChannel.close();
                channelGroup.shutdown();
                executor.shutdown();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
