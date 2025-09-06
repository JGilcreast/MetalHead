package com.github.mibs510;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import com.google.protobuf.InvalidProtocolBufferException;
import com.github.mibs510.StatusIndicatorsOuterClass.StatusIndicators;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {

    public static void main(String[] args) {
        String hostname = "192.168.1.192";
        int port = 2323;

        try (Socket socket = new Socket(hostname, port)) {

            System.out.println("Connected to server at " + hostname + ":" + port);

            OutputStream outputStream = socket.getOutputStream();
            outputStream.write("Hello MetalHead".getBytes());
            outputStream.flush();

            InputStream inputStream = socket.getInputStream();

            while (inputStream.available() == 0) {} // Wait for the server to respond

            System.out.println("inputStream.available() = " + inputStream.available());

            while (true) {
                byte[] buffer = inputStream.readAllBytes();

                StatusIndicators statusIndicators = StatusIndicators.parseFrom(buffer);

                System.out.println("SHEAR_CUT = " + statusIndicators.getShearCut());
                System.out.println("SHEAR_HOME = " +  statusIndicators.getShearHome());
                System.out.println("TOOL_OUT = " + statusIndicators.getToolOut());
                System.out.println("TOOL_IN = " +  statusIndicators.getToolIn());
                System.out.println("FEED_FORWARD = " + statusIndicators.getFeedForward());
                System.out.println("FEED_REVERSE = " +  statusIndicators.getFeedReverse());
                System.out.println("HEAD_CW = " + statusIndicators.getHeadCw());
                System.out.println("HEAD_CCW = " +  statusIndicators.getHeadCcw());
                System.out.println("HEAD_OUT = " + statusIndicators.getHeadOut());
                System.out.println("HEAD_IN = " +  statusIndicators.getHeadIn());
                System.out.println("ENCODER_FEED_SET = " + statusIndicators.getEncoderFeedSet());
                System.out.println("ENCODER_FEED_RESET = " +  statusIndicators.getEncoderFeedReset());
                System.out.println("ENCODER_BEND_SET = " + statusIndicators.getEncoderBendSet());
                System.out.println("ENCODER_BEND_RESET = " +  statusIndicators.getEncoderFeedReset());
                System.out.println("PROXIMITY_HEAD_OUT = " + statusIndicators.getProximityHeadOut());
                System.out.println("PROXIMITY_HEAD_IN = " +  statusIndicators.getProximityHeadIn());
                System.out.println("PROXIMITY_SHEAR_HOME = " + statusIndicators.getProximityShearHome());
                System.out.println("PROXIMITY_SHEAR_CUT = " +  statusIndicators.getProximityShearCut());
                System.out.println("PROXIMITY_TOOL_IN = " + statusIndicators.getProximityToolIn());
                System.out.println("PROXIMITY_TOOL_OUT = " +  statusIndicators.getProximityToolOut());
                System.out.println("SHEAR_BUTTON = " + statusIndicators.getShearButton());
                System.out.println("PROXIMITY_HEAD_LIMIT = " +  statusIndicators.getProximityHeadLimit());
                System.out.println("PROXIMITY_HEAD_CW = " + statusIndicators.getProximityHeadCw());
                System.out.println("PROXIMITY_HEAD_CCW = " +  statusIndicators.getProximityHeadCcw());
                System.out.println("AUTO_BUTTON = " + statusIndicators.getAutoButton());
                System.out.println("ESTOP = " +  statusIndicators.getEStop());
                System.out.println("FUSE = " + statusIndicators.getFuse());
                System.out.println("encoderFeedCount = " +  statusIndicators.getEncoderFeedCount());
                System.out.println("encoderBendCount = " + statusIndicators.getEncoderBendCount());
                System.out.println("TWENTY_FOUR_VRAW_BUS_VOLTAGE = " +  statusIndicators.getTwelveVBusVoltage());
                System.out.println("TWENTY_FOUR_VRAW_BUS_CURRENT = " + statusIndicators.getTwentyFourVrawBusCurrent());
                System.out.println("AUX_TWENTY_FOUR_V_BUS_VOLTAGE = " +  statusIndicators.getAuxTwentyFourVBusVoltage());
                System.out.println("AUX_TWENTY_FOUR_V_BUS_CURRENT = " + statusIndicators.getAuxTwentyFourVBusCurrent());
                System.out.println("TWELVE_V_BUS_VOLTAGE = " +  statusIndicators.getTwelveVBusVoltage());
                System.out.println("TWELVE_V_BUS_CURRENT = " + statusIndicators.getTwelveVBusCurrent());
                System.out.println("FIVE_V_BUS_VOLTAGE = " +  statusIndicators.getFiveVBusVoltage());
                System.out.println("FIVE_V_BUS_CURRENT = " + statusIndicators.getFiveVBusCurrent());
                System.out.println("THREE_V_THREE_V_BUS_VOLTAGE = " +  statusIndicators.getThreeVThreeVBusVoltage());
                System.out.println("THREE_V_THREE_V_BUS_CURRENT = " + statusIndicators.getThreeVThreeVBusCurrent());
                System.out.println("FGND_BUS_VOLTAGE = " +  statusIndicators.getFGndBusVoltage());
                System.out.println("FGND_BUS_CURRENT = " +  statusIndicators.getFGndBusCurrent());
            }

//            outputStream.close();
//            inputStream.close();

        } catch (UnknownHostException e) {
            System.err.println("Server not found: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
        }
    }
}