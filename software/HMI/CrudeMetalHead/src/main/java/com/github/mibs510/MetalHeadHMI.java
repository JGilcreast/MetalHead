package com.github.mibs510;

import java.awt.event.*;

import com.formdev.flatlaf.themes.FlatMacDarkLaf;
import com.intellij.uiDesigner.core.*;

import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MetalHeadHMI extends JFrame {
    private final AsyncTCPClient tcpClient;
    private final DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern("MM/dd/yyyy HH:mm:ss.SSS");

    public MetalHeadHMI() throws IOException {
        tcpClient = new AsyncTCPClient(this::onMessageReceived, this::updateUiComponents);

        FlatMacDarkLaf.setup();
        initComponents();
        // Center on screen
        hmiFrame.setLocationRelativeTo(null);
        // Show the GUI
        hmiFrame.setVisible(true);
        // If we click on the X on the top right, close it
        hmiFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // Pad the size of the frame (hmiFrame) to accommodate the text/labels within
        // hmiFrame.pack();

        // Connect to server
        tcpClient.connect("192.168.1.36", 3682);
    }

    // Callback method to update the GUI from a background thread
    private void onMessageReceived(String message) {
        String formattedDateTime = LocalDateTime.now().format(dateTimeFormatter);
        final String msg = ("[" + formattedDateTime + "] " +
                message + "\n").replaceAll("(\\r?\\n)+", "\n");
        EventQueue.invokeLater(() -> debugTextArea.append(msg));
    }

    private void updateUiComponents(HmiServerMsgProto.HmiServerMsg hmiClientMsg) {
        // Everything below only needs to be set once at the start of the program.
        firmwareVersionValueLabel.setText(String.format("%d.%d.%d",
                hmiClientMsg.getHmiClientMsg().getMajorVersion(),
                hmiClientMsg.getHmiClientMsg().getMinorVersion(),
                hmiClientMsg.getHmiClientMsg().getPatchVersion()));

        bootCountValueLabel.setText(String.format("%d", hmiClientMsg.getHmiClientMsg().getBootCount()));

        StringBuilder serialNumber = new StringBuilder();
        for (int i = 0; i < hmiClientMsg.getHmiClientMsg().getSerialNumber().size(); i++) {
            serialNumber.append(hmiClientMsg.getHmiClientMsg().getSerialNumber().byteAt(i) & 0xFF);
        }
        serialNumberValueLabel.setText(serialNumber.toString());

        StringBuilder macAddress = new StringBuilder();
        for (int i = 0; i < hmiClientMsg.getHmiClientMsg().getMacAddress().size(); i++) {
            macAddress.append(String.format("%02X", hmiClientMsg.getHmiClientMsg().getMacAddress().byteAt(i) & 0xFF));
            if (i < hmiClientMsg.getHmiClientMsg().getMacAddress().size() - 1) {
                macAddress.append(":");
            }
        }
        macAddressValueLabel.setText(macAddress.toString());

        StringBuilder ipAddress = new StringBuilder();
        for (int i = 0; i < hmiClientMsg.getHmiClientMsg().getIpAddress().size(); i++) {
            ipAddress.append(hmiClientMsg.getHmiClientMsg().getIpAddress().byteAt(i) & 0xFF);
            if (i < hmiClientMsg.getHmiClientMsg().getIpAddress().size() - 1) {
                ipAddress.append(".");
            }
        }
        ipAddressValueLabel.setText(ipAddress.toString());

        StringBuilder subnetMask = new StringBuilder();
        for (int i = 0; i < hmiClientMsg.getHmiClientMsg().getSubnetMask().size(); i++) {
            subnetMask.append(hmiClientMsg.getHmiClientMsg().getSubnetMask().byteAt(i) & 0xFF);
            if (i < hmiClientMsg.getHmiClientMsg().getSubnetMask().size() - 1) {
                subnetMask.append(".");
            }
        }
        subnetMaskValueLabel.setText(subnetMask.toString());

        portValueLabel.setText(String.format("%d", hmiClientMsg.getHmiClientMsg().getPort()));

        StringBuilder hmiIpAddress = new StringBuilder();
        for (int i = 0; i < hmiClientMsg.getHmiClientMsg().getHmiIpAddress().size(); i++) {
            hmiIpAddress.append(hmiClientMsg.getHmiClientMsg().getHmiIpAddress().byteAt(i) & 0xFF);
            if (i < hmiClientMsg.getHmiClientMsg().getHmiIpAddress().size() - 1) {
                hmiIpAddress.append(".");
            }
        }
        hmiIpAddressValueLabel.setText(hmiIpAddress.toString());

        hmiPortValueLabel.setText(String.format("%d", hmiClientMsg.getHmiClientMsg().getHmiPort()));

        solenoidShearCutCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getShearCut());
        solenoidShearHomeCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getShearHome());
        solenoidToolOutCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getToolOut());
        solenoidToolInCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getToolIn());
        solenoidFeedForwardCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getFeedForward());
        solenoidFeedReverseCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getFeedReverse());
        solenoidHeadCwCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getHeadCw());
        solenoidHeadCcwCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getHeadCcw());
        solenoidHeadOutCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getHeadOut());
        solenoidHeadInCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getHeadIn());
        encoderFeedSetCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getEncoderFeedSet());
        encoderFeedResetCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getEncoderFeedReset());
        encoderBendSetCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getEncoderBendSet());
        encoderBendResetCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getEncoderBendReset());
        proximityHeadOutCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getProximityHeadOut());
        proximityHeadInCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getProximityHeadIn());
        proximityShearHomeCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getProximityShearHome());
        proximityShearCutCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getProximityShearCut());
        proximityToolInCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getProximityToolIn());
        proximityToolOutCheckbox.setSelected(hmiClientMsg.getHmiClientMsg().getProximityToolOut());
        buttonShearCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getShearButton());
        proximityHeadLimitCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getProximityHeadLimit());
        proximityHeadCwCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getProximityHeadCw());
        proximityHeadCcwCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getProximityHeadCcw());
        buttonAutoCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getAutoButton());
        buttonEstopCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getEStop());
        fuseCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getFuse());
        twentyFourVRawCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getVRawTwentyFour());
        auxTwentyFourVCheckBox.setSelected(hmiClientMsg.getHmiClientMsg().getAuxTwentyFourV());
        encoderFeedCountValueLabel.setText(String.format("%d", hmiClientMsg.getHmiClientMsg().getEncoderFeedCount()));
        encoderBendCountValueLabel.setText(String.format("%d", hmiClientMsg.getHmiClientMsg().getEncoderBendCount()));
        twentyFourVRawVoltValueLabel.setText(Float.toString(
                hmiClientMsg.getHmiClientMsg().getTwentyFourVrawBusVoltage()));
        twentyFourVRawCurrentValueLabel.setText(Float.toString(
                hmiClientMsg.getHmiClientMsg().getTwentyFourVrawBusCurrent()));
        aux24vVoltValueLabel.setText(Float.toString(hmiClientMsg.getHmiClientMsg().getAuxTwentyFourVBusVoltage()));
        aux24vCurrentValueLabel.setText(Float.toString(hmiClientMsg.getHmiClientMsg().getAuxTwentyFourVBusCurrent()));
        twelvevVoltValueLabel.setText(Float.toString(hmiClientMsg.getHmiClientMsg().getTwelveVBusVoltage()));
        twelvevCurrentValueLabel.setText(Float.toString(hmiClientMsg.getHmiClientMsg().getTwelveVBusCurrent()));
        fivevVoltValueLabel.setText(Float.toString(hmiClientMsg.getHmiClientMsg().getFiveVBusVoltage()));
        fivevCurrentValueLabel.setText(Float.toString(hmiClientMsg.getHmiClientMsg().getFiveVBusCurrent()));
        threevThreeVoltValueLabel.setText(Float.toString(hmiClientMsg.getHmiClientMsg().getThreeVThreeVBusVoltage()));
        threevThreeCurrentValueLabel.setText(
                Float.toString(hmiClientMsg.getHmiClientMsg().getThreeVThreeVBusCurrent()));
        fGndVoltValueLabel.setText(Float.toString(hmiClientMsg.getHmiClientMsg().getFGndBusVoltage()));
        fGndCurrentValueLabel.setText(Float.toString(hmiClientMsg.getHmiClientMsg().getFGndBusCurrent()));
        stateValueLabel.setText(hmiClientMsg.getHmiClientMsg().getState().toString());
        actionValueLabel.setText(hmiClientMsg.getHmiClientMsg().getAction().toString());
        // Right size the main JFrame, or else the Misc column gets cutoff
        hmiFrame.pack();
    }

    private void onStatusUpdate(String status) {
        EventQueue.invokeLater(() -> debugTextArea.append("Status: " + status + "\n"));
    }

    public static void main(String[] args) {
        // Start the Swing application on the EDT
        EventQueue.invokeLater(() -> {
            try {
                new MetalHeadHMI();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }

    private void openMakeShapeWindow(ActionEvent e) {
        // Make the Dialog window visible in the center of the parent Frame (hmiFrame)
        makeShapeJDialog.setLocationRelativeTo(this.hmiFrame);
        // This makes the parent Frame (hmiFrame) inaccessible while this is open
        makeShapeJDialog.setModalityType(Dialog.ModalityType.APPLICATION_MODAL);
        makeShapeJDialog.setVisible(true);
    }

    private void manualActionsButtonClicked(ActionEvent e) {
        // Make the Dialog window visible in the center of the parent Frame (hmiFrame)
        manualActionsJDialog.setLocationRelativeTo(this.hmiFrame);
        // This makes the parent Frame (hmiFrame) inaccessible while this is open
        manualActionsJDialog.setModalityType(Dialog.ModalityType.APPLICATION_MODAL);
        manualActionsJDialog.setVisible(true);
    }

    private void headOut(ActionEvent e) {
        HmiClientMsgProto.HmiClientMessage msg = HmiClientMsgProto.HmiClientMessage.newBuilder()
                .setHmiClientActionValue(HmiClientMsgProto.HmiClientMessage.HMICLIENTACTION_FIELD_NUMBER)
                .setHmiClientAction(HmiClientMsgProto.HmiClientAction.ACTION_HEAD_OUT)
                .build();
        tcpClient.sendMessage(msg);
    }

	public void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents  @formatter:off
        // Generated using JFormDesigner Educational license - Connor McMillan
        hmiFrame = new JFrame();
        statusIndicatorsLabelPanel = new JPanel();
        statusIndicatorsLabel = new JLabel();
        everythingelsePanel = new JPanel();
        solenoidsLabel = new JLabel();
        encodersLabel = new JLabel();
        proximitySensorLabel = new JLabel();
        buttonsLabel = new JLabel();
        currentMonitorLabel = new JLabel();
        miscLabel = new JLabel();
        solenoidsPanel = new JPanel();
        solenoidShearCutCheckBox = new JCheckBox();
        solenoidShearHomeCheckBox = new JCheckBox();
        solenoidToolOutCheckBox = new JCheckBox();
        solenoidToolInCheckBox = new JCheckBox();
        solenoidFeedForwardCheckBox = new JCheckBox();
        solenoidFeedReverseCheckBox = new JCheckBox();
        solenoidHeadCwCheckBox = new JCheckBox();
        solenoidHeadCcwCheckBox = new JCheckBox();
        solenoidHeadOutCheckBox = new JCheckBox();
        solenoidHeadInCheckBox = new JCheckBox();
        encodersPanel = new JPanel();
        encoderFeedSetCheckBox = new JCheckBox();
        encoderFeedResetCheckBox = new JCheckBox();
        encoderBendSetCheckBox = new JCheckBox();
        encoderBendResetCheckBox = new JCheckBox();
        encoderFeedCountLabel = new JLabel();
        encoderFeedCountValueLabel = new JLabel();
        encoderBendCountLabel = new JLabel();
        encoderBendCountValueLabel = new JLabel();
        proximitySensorsPanel = new JPanel();
        proximityHeadOutCheckBox = new JCheckBox();
        proximityHeadInCheckBox = new JCheckBox();
        proximityShearHomeCheckBox = new JCheckBox();
        proximityShearCutCheckBox = new JCheckBox();
        proximityToolInCheckBox = new JCheckBox();
        proximityToolOutCheckbox = new JCheckBox();
        proximityHeadLimitCheckBox = new JCheckBox();
        proximityHeadCwCheckBox = new JCheckBox();
        proximityHeadCcwCheckBox = new JCheckBox();
        buttonsPanel = new JPanel();
        buttonShearCheckBox = new JCheckBox();
        buttonAutoCheckBox = new JCheckBox();
        buttonEstopCheckBox = new JCheckBox();
        currentMonitorsPanel = new JPanel();
        twentyFourVRawVoltLabel = new JLabel();
        twentyFourVRawVoltValueLabel = new JLabel();
        twentyFourVRawCurrentLabel = new JLabel();
        twentyFourVRawCurrentValueLabel = new JLabel();
        aux24vVoltLabel = new JLabel();
        aux24vVoltValueLabel = new JLabel();
        aux24vCurrentLabel = new JLabel();
        aux24vCurrentValueLabel = new JLabel();
        twelvevVoltLabel = new JLabel();
        twelvevVoltValueLabel = new JLabel();
        twelvevCurrentLabel = new JLabel();
        twelvevCurrentValueLabel = new JLabel();
        fivevVoltLabel = new JLabel();
        fivevVoltValueLabel = new JLabel();
        fivevCurrentLabel = new JLabel();
        fivevCurrentValueLabel = new JLabel();
        threevThreeVoltLabel = new JLabel();
        threevThreeVoltValueLabel = new JLabel();
        threevThreeCurrentLabel = new JLabel();
        threevThreeCurrentValueLabel = new JLabel();
        fGndVoltLabel = new JLabel();
        fGndVoltValueLabel = new JLabel();
        fGndCurrentLabel = new JLabel();
        fGndCurrentValueLabel = new JLabel();
        miscPanel = new JPanel();
        fuseCheckBox = new JCheckBox();
        twentyFourVRawCheckBox = new JCheckBox();
        auxTwentyFourVCheckBox = new JCheckBox();
        interfaceBoardLabel = new JLabel();
        firmwareVersionLabel = new JLabel();
        firmwareVersionValueLabel = new JLabel();
        bootCountLabel = new JLabel();
        bootCountValueLabel = new JLabel();
        serialNumberLabel = new JLabel();
        serialNumberValueLabel = new JLabel();
        macAddressLabel = new JLabel();
        macAddressValueLabel = new JLabel();
        ipAddressLabel = new JLabel();
        ipAddressValueLabel = new JLabel();
        subnetMaskLabel = new JLabel();
        subnetMaskValueLabel = new JLabel();
        portLabel = new JLabel();
        portValueLabel = new JLabel();
        hmiIpAddressLabel = new JLabel();
        hmiIpAddressValueLabel = new JLabel();
        hmiPortLabel = new JLabel();
        hmiPortValueLabel = new JLabel();
        statePanel = new JPanel();
        stateLabel = new JLabel();
        stateValueLabel = new JLabel();
        actionPanel = new JPanel();
        actionLabel = new JLabel();
        actionValueLabel = new JLabel();
        makeShapeButton = new JButton();
        manualActionsButton = new JButton();
        debugLogLabel = new JLabel();
        debugLogScrollPane = new JScrollPane();
        debugTextArea = new JTextArea();
        makeShapeJDialog = new JDialog();
        makeShapePanel = new JPanel();
        makeShapeScrollPane = new JScrollPane();
        makeShapeRowsPanel = new JPanel();
        lengthLabel = new JLabel();
        lengthTextField = new JTextField();
        bendDegreeLabel = new JLabel();
        bendDegreeTextField = new JTextField();
        directionLabel = new JLabel();
        directionComboBox = new JComboBox();
        lengthCompLabel = new JLabel();
        lengthCompTextField = new JTextField();
        bendCompLabel = new JLabel();
        bendCompTextField = new JTextField();
        addLineSendPanel = new JPanel();
        addLineButton = new JButton();
        sendButton = new JButton();
        manualActionsJDialog = new JDialog();
        manualActionsPanel = new JPanel();
        headOutButton = new JButton();
        headInButton = new JButton();
        shearHomeButton = new JButton();
        shearCutButton = new JButton();
        toolInButton = new JButton();
        toolOutButton = new JButton();
        headLimitButton = new JButton();
        headCwButton = new JButton();
        headCcwButton = new JButton();
        feedForwardButton = new JButton();
        feedReverseButton = new JButton();
        eStopButton = new JButton();

        //======== hmiFrame ========
        {
            hmiFrame.setTitle("MetalHead HMI - Crude Edition");
            hmiFrame.setIconImage(new ImageIcon(getClass().getResource("/MH-W-64.png")).getImage());
            var hmiFrameContentPane = hmiFrame.getContentPane();
            hmiFrameContentPane.setLayout(new GridLayoutManager(5, 3, new Insets(10, 10, 10, 10), -1, -1));

            //======== statusIndicatorsLabelPanel ========
            {
                statusIndicatorsLabelPanel.setLayout(new GridLayoutManager(3, 3, new Insets(0, 0, 0, 0), -1, -1));

                //---- statusIndicatorsLabel ----
                statusIndicatorsLabel.setText("Status Indicators");
                statusIndicatorsLabel.setFont(new Font("Inter", Font.BOLD, 26));
                statusIndicatorsLabelPanel.add(statusIndicatorsLabel, new GridConstraints(1, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
            }
            hmiFrameContentPane.add(statusIndicatorsLabelPanel, new GridConstraints(0, 1, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //======== everythingelsePanel ========
            {
                everythingelsePanel.setLayout(new GridLayoutManager(5, 6, new Insets(10, 10, 10, 10), -1, -1));

                //---- solenoidsLabel ----
                solenoidsLabel.setText("Solenoids");
                solenoidsLabel.setFont(new Font("Inter", Font.BOLD, 20));
                everythingelsePanel.add(solenoidsLabel, new GridConstraints(0, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- encodersLabel ----
                encodersLabel.setText("Encoders");
                encodersLabel.setFont(new Font("Inter", Font.BOLD, 20));
                everythingelsePanel.add(encodersLabel, new GridConstraints(0, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- proximitySensorLabel ----
                proximitySensorLabel.setText("Proximity Sensors");
                proximitySensorLabel.setFont(new Font("Inter", Font.BOLD, 20));
                everythingelsePanel.add(proximitySensorLabel, new GridConstraints(0, 2, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- buttonsLabel ----
                buttonsLabel.setText("Buttons");
                buttonsLabel.setFont(new Font("Inter", Font.BOLD, 20));
                everythingelsePanel.add(buttonsLabel, new GridConstraints(0, 3, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- currentMonitorLabel ----
                currentMonitorLabel.setText("Current Monitors");
                currentMonitorLabel.setFont(new Font("Inter", Font.BOLD, 20));
                everythingelsePanel.add(currentMonitorLabel, new GridConstraints(0, 4, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- miscLabel ----
                miscLabel.setText("Misc");
                miscLabel.setFont(new Font("Inter", Font.BOLD, 20));
                everythingelsePanel.add(miscLabel, new GridConstraints(0, 5, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //======== solenoidsPanel ========
                {
                    solenoidsPanel.setLayout(new GridLayoutManager(5, 3, new Insets(0, 10, 0, 0), -1, -1));

                    //---- solenoidShearCutCheckBox ----
                    solenoidShearCutCheckBox.setText("SHEAR CUT");
                    solenoidsPanel.add(solenoidShearCutCheckBox, new GridConstraints(0, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- solenoidShearHomeCheckBox ----
                    solenoidShearHomeCheckBox.setText("SHEAR HOME");
                    solenoidShearHomeCheckBox.setHorizontalAlignment(SwingConstants.LEFT);
                    solenoidsPanel.add(solenoidShearHomeCheckBox, new GridConstraints(0, 2, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- solenoidToolOutCheckBox ----
                    solenoidToolOutCheckBox.setText("TOOL OUT");
                    solenoidsPanel.add(solenoidToolOutCheckBox, new GridConstraints(1, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- solenoidToolInCheckBox ----
                    solenoidToolInCheckBox.setText("TOOL IN");
                    solenoidsPanel.add(solenoidToolInCheckBox, new GridConstraints(1, 2, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- solenoidFeedForwardCheckBox ----
                    solenoidFeedForwardCheckBox.setText("FEED FORWARD");
                    solenoidsPanel.add(solenoidFeedForwardCheckBox, new GridConstraints(2, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- solenoidFeedReverseCheckBox ----
                    solenoidFeedReverseCheckBox.setText("FEED REVERSE");
                    solenoidsPanel.add(solenoidFeedReverseCheckBox, new GridConstraints(2, 2, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- solenoidHeadCwCheckBox ----
                    solenoidHeadCwCheckBox.setText("HEAD CW");
                    solenoidsPanel.add(solenoidHeadCwCheckBox, new GridConstraints(3, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- solenoidHeadCcwCheckBox ----
                    solenoidHeadCcwCheckBox.setText("HEAD CCW");
                    solenoidsPanel.add(solenoidHeadCcwCheckBox, new GridConstraints(3, 2, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- solenoidHeadOutCheckBox ----
                    solenoidHeadOutCheckBox.setText("HEAD OUT");
                    solenoidsPanel.add(solenoidHeadOutCheckBox, new GridConstraints(4, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- solenoidHeadInCheckBox ----
                    solenoidHeadInCheckBox.setText("HEAD IN");
                    solenoidsPanel.add(solenoidHeadInCheckBox, new GridConstraints(4, 2, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                }
                everythingelsePanel.add(solenoidsPanel, new GridConstraints(1, 0, 1, 1,
                    GridConstraints.ANCHOR_NORTH, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //======== encodersPanel ========
                {
                    encodersPanel.setLayout(new GridLayoutManager(4, 3, new Insets(0, 10, 0, 0), -1, -1));

                    //---- encoderFeedSetCheckBox ----
                    encoderFeedSetCheckBox.setText("FEED SET");
                    encodersPanel.add(encoderFeedSetCheckBox, new GridConstraints(0, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- encoderFeedResetCheckBox ----
                    encoderFeedResetCheckBox.setText("FEED RESET");
                    encodersPanel.add(encoderFeedResetCheckBox, new GridConstraints(0, 2, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- encoderBendSetCheckBox ----
                    encoderBendSetCheckBox.setText("BEND SET");
                    encodersPanel.add(encoderBendSetCheckBox, new GridConstraints(1, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- encoderBendResetCheckBox ----
                    encoderBendResetCheckBox.setText("BEND RESET");
                    encodersPanel.add(encoderBendResetCheckBox, new GridConstraints(1, 2, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- encoderFeedCountLabel ----
                    encoderFeedCountLabel.setText("Encoder Feed Count:");
                    encodersPanel.add(encoderFeedCountLabel, new GridConstraints(2, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    encodersPanel.add(encoderFeedCountValueLabel, new GridConstraints(2, 2, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- encoderBendCountLabel ----
                    encoderBendCountLabel.setText("Encoder Bend Count:");
                    encodersPanel.add(encoderBendCountLabel, new GridConstraints(3, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    encodersPanel.add(encoderBendCountValueLabel, new GridConstraints(3, 2, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                }
                everythingelsePanel.add(encodersPanel, new GridConstraints(1, 1, 1, 1,
                    GridConstraints.ANCHOR_NORTH, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //======== proximitySensorsPanel ========
                {
                    proximitySensorsPanel.setLayout(new GridLayoutManager(6, 2, new Insets(0, 0, 0, 0), -1, -1));

                    //---- proximityHeadOutCheckBox ----
                    proximityHeadOutCheckBox.setText("HEAD OUT");
                    proximitySensorsPanel.add(proximityHeadOutCheckBox, new GridConstraints(0, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- proximityHeadInCheckBox ----
                    proximityHeadInCheckBox.setText("HEAD IN");
                    proximitySensorsPanel.add(proximityHeadInCheckBox, new GridConstraints(0, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- proximityShearHomeCheckBox ----
                    proximityShearHomeCheckBox.setText("SHEAR HOME");
                    proximitySensorsPanel.add(proximityShearHomeCheckBox, new GridConstraints(1, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- proximityShearCutCheckBox ----
                    proximityShearCutCheckBox.setText("SHEAR CUT");
                    proximitySensorsPanel.add(proximityShearCutCheckBox, new GridConstraints(1, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- proximityToolInCheckBox ----
                    proximityToolInCheckBox.setText("TOOL IN");
                    proximitySensorsPanel.add(proximityToolInCheckBox, new GridConstraints(2, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- proximityToolOutCheckbox ----
                    proximityToolOutCheckbox.setText("TOOL OUT");
                    proximitySensorsPanel.add(proximityToolOutCheckbox, new GridConstraints(2, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- proximityHeadLimitCheckBox ----
                    proximityHeadLimitCheckBox.setText("HEAD LIMIT");
                    proximitySensorsPanel.add(proximityHeadLimitCheckBox, new GridConstraints(3, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- proximityHeadCwCheckBox ----
                    proximityHeadCwCheckBox.setText("HEAD CW");
                    proximitySensorsPanel.add(proximityHeadCwCheckBox, new GridConstraints(3, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- proximityHeadCcwCheckBox ----
                    proximityHeadCcwCheckBox.setText("HEAD CCW");
                    proximitySensorsPanel.add(proximityHeadCcwCheckBox, new GridConstraints(4, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                }
                everythingelsePanel.add(proximitySensorsPanel, new GridConstraints(1, 2, 1, 1,
                    GridConstraints.ANCHOR_NORTH, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //======== buttonsPanel ========
                {
                    buttonsPanel.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));

                    //---- buttonShearCheckBox ----
                    buttonShearCheckBox.setText("SHEAR");
                    buttonsPanel.add(buttonShearCheckBox, new GridConstraints(0, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- buttonAutoCheckBox ----
                    buttonAutoCheckBox.setText("AUTO");
                    buttonsPanel.add(buttonAutoCheckBox, new GridConstraints(1, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- buttonEstopCheckBox ----
                    buttonEstopCheckBox.setText("ESTOP");
                    buttonsPanel.add(buttonEstopCheckBox, new GridConstraints(2, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                }
                everythingelsePanel.add(buttonsPanel, new GridConstraints(1, 3, 1, 1,
                    GridConstraints.ANCHOR_NORTH, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //======== currentMonitorsPanel ========
                {
                    currentMonitorsPanel.setLayout(new GridLayoutManager(12, 2, new Insets(0, 0, 0, 0), -1, -1));

                    //---- twentyFourVRawVoltLabel ----
                    twentyFourVRawVoltLabel.setText("24VRAW:");
                    currentMonitorsPanel.add(twentyFourVRawVoltLabel, new GridConstraints(0, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(twentyFourVRawVoltValueLabel, new GridConstraints(0, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- twentyFourVRawCurrentLabel ----
                    twentyFourVRawCurrentLabel.setText("24VRAW Current:");
                    currentMonitorsPanel.add(twentyFourVRawCurrentLabel, new GridConstraints(1, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(twentyFourVRawCurrentValueLabel, new GridConstraints(1, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- aux24vVoltLabel ----
                    aux24vVoltLabel.setText("AUX24V:");
                    currentMonitorsPanel.add(aux24vVoltLabel, new GridConstraints(2, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(aux24vVoltValueLabel, new GridConstraints(2, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- aux24vCurrentLabel ----
                    aux24vCurrentLabel.setText("AUX24V Current:");
                    currentMonitorsPanel.add(aux24vCurrentLabel, new GridConstraints(3, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(aux24vCurrentValueLabel, new GridConstraints(3, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- twelvevVoltLabel ----
                    twelvevVoltLabel.setText("12V:");
                    currentMonitorsPanel.add(twelvevVoltLabel, new GridConstraints(4, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(twelvevVoltValueLabel, new GridConstraints(4, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- twelvevCurrentLabel ----
                    twelvevCurrentLabel.setText("12V Current:");
                    currentMonitorsPanel.add(twelvevCurrentLabel, new GridConstraints(5, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(twelvevCurrentValueLabel, new GridConstraints(5, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- fivevVoltLabel ----
                    fivevVoltLabel.setText("5V:");
                    currentMonitorsPanel.add(fivevVoltLabel, new GridConstraints(6, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(fivevVoltValueLabel, new GridConstraints(6, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- fivevCurrentLabel ----
                    fivevCurrentLabel.setText("5V Current:");
                    currentMonitorsPanel.add(fivevCurrentLabel, new GridConstraints(7, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(fivevCurrentValueLabel, new GridConstraints(7, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- threevThreeVoltLabel ----
                    threevThreeVoltLabel.setText("3V3:");
                    currentMonitorsPanel.add(threevThreeVoltLabel, new GridConstraints(8, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(threevThreeVoltValueLabel, new GridConstraints(8, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- threevThreeCurrentLabel ----
                    threevThreeCurrentLabel.setText("3V3 Current:");
                    currentMonitorsPanel.add(threevThreeCurrentLabel, new GridConstraints(9, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(threevThreeCurrentValueLabel, new GridConstraints(9, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- fGndVoltLabel ----
                    fGndVoltLabel.setText("FGND:");
                    currentMonitorsPanel.add(fGndVoltLabel, new GridConstraints(10, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(fGndVoltValueLabel, new GridConstraints(10, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- fGndCurrentLabel ----
                    fGndCurrentLabel.setText("FGND Current:");
                    currentMonitorsPanel.add(fGndCurrentLabel, new GridConstraints(11, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    currentMonitorsPanel.add(fGndCurrentValueLabel, new GridConstraints(11, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                }
                everythingelsePanel.add(currentMonitorsPanel, new GridConstraints(1, 4, 1, 1,
                    GridConstraints.ANCHOR_NORTH, GridConstraints.FILL_HORIZONTAL,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //======== miscPanel ========
                {
                    miscPanel.setLayout(new GridLayoutManager(13, 2, new Insets(0, 0, 0, 10), -1, -1));

                    //---- fuseCheckBox ----
                    fuseCheckBox.setText("FUSE");
                    miscPanel.add(fuseCheckBox, new GridConstraints(0, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- twentyFourVRawCheckBox ----
                    twentyFourVRawCheckBox.setText("24VRAW");
                    miscPanel.add(twentyFourVRawCheckBox, new GridConstraints(1, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- auxTwentyFourVCheckBox ----
                    auxTwentyFourVCheckBox.setText("AUX24V");
                    miscPanel.add(auxTwentyFourVCheckBox, new GridConstraints(2, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- interfaceBoardLabel ----
                    interfaceBoardLabel.setText("Interface Board");
                    miscPanel.add(interfaceBoardLabel, new GridConstraints(3, 0, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- firmwareVersionLabel ----
                    firmwareVersionLabel.setText("Firmware Version:");
                    miscPanel.add(firmwareVersionLabel, new GridConstraints(4, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    miscPanel.add(firmwareVersionValueLabel, new GridConstraints(4, 1, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- bootCountLabel ----
                    bootCountLabel.setText("Boot Count:");
                    miscPanel.add(bootCountLabel, new GridConstraints(5, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    miscPanel.add(bootCountValueLabel, new GridConstraints(5, 1, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- serialNumberLabel ----
                    serialNumberLabel.setText("Serial Number:");
                    miscPanel.add(serialNumberLabel, new GridConstraints(6, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    miscPanel.add(serialNumberValueLabel, new GridConstraints(6, 1, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- macAddressLabel ----
                    macAddressLabel.setText("MAC Address:");
                    miscPanel.add(macAddressLabel, new GridConstraints(7, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    miscPanel.add(macAddressValueLabel, new GridConstraints(7, 1, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- ipAddressLabel ----
                    ipAddressLabel.setText("IP Address:");
                    miscPanel.add(ipAddressLabel, new GridConstraints(8, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    miscPanel.add(ipAddressValueLabel, new GridConstraints(8, 1, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- subnetMaskLabel ----
                    subnetMaskLabel.setText("Subnet Mask:");
                    miscPanel.add(subnetMaskLabel, new GridConstraints(9, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    miscPanel.add(subnetMaskValueLabel, new GridConstraints(9, 1, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- portLabel ----
                    portLabel.setText("Port:");
                    miscPanel.add(portLabel, new GridConstraints(10, 0, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    miscPanel.add(portValueLabel, new GridConstraints(10, 1, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- hmiIpAddressLabel ----
                    hmiIpAddressLabel.setText("HMI IP Address:");
                    miscPanel.add(hmiIpAddressLabel, new GridConstraints(11, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    miscPanel.add(hmiIpAddressValueLabel, new GridConstraints(11, 1, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- hmiPortLabel ----
                    hmiPortLabel.setText("HMI Port:");
                    miscPanel.add(hmiPortLabel, new GridConstraints(12, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                    miscPanel.add(hmiPortValueLabel, new GridConstraints(12, 1, 1, 1,
                        GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                }
                everythingelsePanel.add(miscPanel, new GridConstraints(1, 5, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //======== statePanel ========
                {
                    statePanel.setLayout(new GridLayoutManager(1, 2, new Insets(0, 0, 0, 0), -1, -1));

                    //---- stateLabel ----
                    stateLabel.setText("State: ");
                    stateLabel.setFont(new Font("Segoe UI", Font.BOLD, 20));
                    statePanel.add(stateLabel, new GridConstraints(0, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- stateValueLabel ----
                    stateValueLabel.setFont(new Font("Segoe UI", Font.BOLD, 20));
                    statePanel.add(stateValueLabel, new GridConstraints(0, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                }
                everythingelsePanel.add(statePanel, new GridConstraints(2, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //======== actionPanel ========
                {
                    actionPanel.setLayout(new GridLayoutManager(1, 2, new Insets(0, 0, 0, 0), -1, -1));

                    //---- actionLabel ----
                    actionLabel.setText("Action:");
                    actionLabel.setFont(new Font("Segoe UI", Font.BOLD, 20));
                    actionPanel.add(actionLabel, new GridConstraints(0, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- actionValueLabel ----
                    actionValueLabel.setFont(new Font("Segoe UI", Font.BOLD, 20));
                    actionPanel.add(actionValueLabel, new GridConstraints(0, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                }
                everythingelsePanel.add(actionPanel, new GridConstraints(2, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- makeShapeButton ----
                makeShapeButton.setText("Make Shape");
                makeShapeButton.addActionListener(e -> openMakeShapeWindow(e));
                everythingelsePanel.add(makeShapeButton, new GridConstraints(3, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- manualActionsButton ----
                manualActionsButton.setText("Manual Actions");
                manualActionsButton.addActionListener(e -> manualActionsButtonClicked(e));
                everythingelsePanel.add(manualActionsButton, new GridConstraints(3, 2, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
            }
            hmiFrameContentPane.add(everythingelsePanel, new GridConstraints(1, 1, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //---- debugLogLabel ----
            debugLogLabel.setText("Debug Log");
            debugLogLabel.setFont(new Font("Inter", Font.BOLD, 26));
            hmiFrameContentPane.add(debugLogLabel, new GridConstraints(2, 1, 1, 1,
                GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //======== debugLogScrollPane ========
            {
                debugLogScrollPane.setPreferredSize(new Dimension(68, 150));

                //---- debugTextArea ----
                debugTextArea.setEditable(false);
                debugLogScrollPane.setViewportView(debugTextArea);
            }
            hmiFrameContentPane.add(debugLogScrollPane, new GridConstraints(3, 1, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));
            hmiFrame.pack();
            hmiFrame.setLocationRelativeTo(hmiFrame.getOwner());
        }

        //======== makeShapeJDialog ========
        {
            makeShapeJDialog.setTitle("Make Shape");
            var makeShapeJDialogContentPane = makeShapeJDialog.getContentPane();
            makeShapeJDialogContentPane.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));

            //======== makeShapePanel ========
            {
                makeShapePanel.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));

                //======== makeShapeScrollPane ========
                {

                    //======== makeShapeRowsPanel ========
                    {
                        makeShapeRowsPanel.setLayout(new GridLayoutManager(3, 10, new Insets(0, 0, 0, 0), -1, -1));

                        //---- lengthLabel ----
                        lengthLabel.setText("Length:");
                        makeShapeRowsPanel.add(lengthLabel, new GridConstraints(0, 0, 1, 1,
                            GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));
                        makeShapeRowsPanel.add(lengthTextField, new GridConstraints(0, 1, 1, 1,
                            GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));

                        //---- bendDegreeLabel ----
                        bendDegreeLabel.setText("Bend Degree:");
                        makeShapeRowsPanel.add(bendDegreeLabel, new GridConstraints(0, 2, 1, 1,
                            GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));
                        makeShapeRowsPanel.add(bendDegreeTextField, new GridConstraints(0, 3, 1, 1,
                            GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));

                        //---- directionLabel ----
                        directionLabel.setText("Direction:");
                        makeShapeRowsPanel.add(directionLabel, new GridConstraints(0, 4, 1, 1,
                            GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));
                        makeShapeRowsPanel.add(directionComboBox, new GridConstraints(0, 5, 1, 1,
                            GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));

                        //---- lengthCompLabel ----
                        lengthCompLabel.setText("Length Comp:");
                        makeShapeRowsPanel.add(lengthCompLabel, new GridConstraints(0, 6, 1, 1,
                            GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));

                        //---- lengthCompTextField ----
                        lengthCompTextField.setCursor(Cursor.getPredefinedCursor(Cursor.TEXT_CURSOR));
                        lengthCompTextField.setFont(new Font("Segoe UI", Font.PLAIN, 12));
                        makeShapeRowsPanel.add(lengthCompTextField, new GridConstraints(0, 7, 1, 1,
                            GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));

                        //---- bendCompLabel ----
                        bendCompLabel.setText("Bend Comp:");
                        makeShapeRowsPanel.add(bendCompLabel, new GridConstraints(0, 8, 1, 1,
                            GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));
                        makeShapeRowsPanel.add(bendCompTextField, new GridConstraints(0, 9, 1, 1,
                            GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                            null, null, null));
                    }
                    makeShapeScrollPane.setViewportView(makeShapeRowsPanel);
                }
                makeShapePanel.add(makeShapeScrollPane, new GridConstraints(0, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //======== addLineSendPanel ========
                {
                    addLineSendPanel.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));

                    //---- addLineButton ----
                    addLineButton.setText("Add Line");
                    addLineSendPanel.add(addLineButton, new GridConstraints(1, 0, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));

                    //---- sendButton ----
                    sendButton.setText("Send");
                    addLineSendPanel.add(sendButton, new GridConstraints(1, 1, 1, 1,
                        GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                        null, null, null));
                }
                makeShapePanel.add(addLineSendPanel, new GridConstraints(1, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
            }
            makeShapeJDialogContentPane.add(makeShapePanel, new GridConstraints(0, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));
            makeShapeJDialog.pack();
            makeShapeJDialog.setLocationRelativeTo(makeShapeJDialog.getOwner());
        }

        //======== manualActionsJDialog ========
        {
            manualActionsJDialog.setTitle("Manual Actions");
            var manualActionsJDialogContentPane = manualActionsJDialog.getContentPane();
            manualActionsJDialogContentPane.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));

            //======== manualActionsPanel ========
            {
                manualActionsPanel.setLayout(new GridLayoutManager(4, 3, new Insets(10, 10, 10, 10), -1, -1));

                //---- headOutButton ----
                headOutButton.setText("Head Out");
                headOutButton.addActionListener(e -> headOut(e));
                manualActionsPanel.add(headOutButton, new GridConstraints(0, 0, 1, 1,
                    GridConstraints.ANCHOR_WEST, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- headInButton ----
                headInButton.setText("Head In");
                manualActionsPanel.add(headInButton, new GridConstraints(0, 1, 1, 1,
                    GridConstraints.ANCHOR_WEST, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- shearHomeButton ----
                shearHomeButton.setText("Shear Home");
                manualActionsPanel.add(shearHomeButton, new GridConstraints(0, 2, 1, 1,
                    GridConstraints.ANCHOR_WEST, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- shearCutButton ----
                shearCutButton.setText("Shear Cut");
                manualActionsPanel.add(shearCutButton, new GridConstraints(1, 0, 1, 1,
                    GridConstraints.ANCHOR_WEST, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- toolInButton ----
                toolInButton.setText("Tool In");
                manualActionsPanel.add(toolInButton, new GridConstraints(1, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- toolOutButton ----
                toolOutButton.setText("Tool Out");
                manualActionsPanel.add(toolOutButton, new GridConstraints(1, 2, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- headLimitButton ----
                headLimitButton.setText("Head Limit");
                manualActionsPanel.add(headLimitButton, new GridConstraints(2, 0, 1, 1,
                    GridConstraints.ANCHOR_WEST, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- headCwButton ----
                headCwButton.setText("Head CW");
                manualActionsPanel.add(headCwButton, new GridConstraints(2, 1, 1, 1,
                    GridConstraints.ANCHOR_WEST, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- headCcwButton ----
                headCcwButton.setText("Head CCW");
                manualActionsPanel.add(headCcwButton, new GridConstraints(2, 2, 1, 1,
                    GridConstraints.ANCHOR_WEST, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- feedForwardButton ----
                feedForwardButton.setText("Feed Forward");
                manualActionsPanel.add(feedForwardButton, new GridConstraints(3, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- feedReverseButton ----
                feedReverseButton.setText("Feed Reverse");
                manualActionsPanel.add(feedReverseButton, new GridConstraints(3, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- eStopButton ----
                eStopButton.setText("ESTOP");
                manualActionsPanel.add(eStopButton, new GridConstraints(3, 2, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
            }
            manualActionsJDialogContentPane.add(manualActionsPanel, new GridConstraints(0, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));
            manualActionsJDialog.pack();
            manualActionsJDialog.setLocationRelativeTo(manualActionsJDialog.getOwner());
        }
		// JFormDesigner - End of component initialization  //GEN-END:initComponents  @formatter:on
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables  @formatter:off
    // Generated using JFormDesigner Educational license - Connor McMillan
    JFrame hmiFrame;
    JPanel statusIndicatorsLabelPanel;
    JLabel statusIndicatorsLabel;
    JPanel everythingelsePanel;
    JLabel solenoidsLabel;
    JLabel encodersLabel;
    JLabel proximitySensorLabel;
    JLabel buttonsLabel;
    JLabel currentMonitorLabel;
    JLabel miscLabel;
    JPanel solenoidsPanel;
    JCheckBox solenoidShearCutCheckBox;
    JCheckBox solenoidShearHomeCheckBox;
    JCheckBox solenoidToolOutCheckBox;
    JCheckBox solenoidToolInCheckBox;
    JCheckBox solenoidFeedForwardCheckBox;
    JCheckBox solenoidFeedReverseCheckBox;
    JCheckBox solenoidHeadCwCheckBox;
    JCheckBox solenoidHeadCcwCheckBox;
    JCheckBox solenoidHeadOutCheckBox;
    JCheckBox solenoidHeadInCheckBox;
    JPanel encodersPanel;
    JCheckBox encoderFeedSetCheckBox;
    JCheckBox encoderFeedResetCheckBox;
    JCheckBox encoderBendSetCheckBox;
    JCheckBox encoderBendResetCheckBox;
    JLabel encoderFeedCountLabel;
    JLabel encoderFeedCountValueLabel;
    JLabel encoderBendCountLabel;
    JLabel encoderBendCountValueLabel;
    JPanel proximitySensorsPanel;
    JCheckBox proximityHeadOutCheckBox;
    JCheckBox proximityHeadInCheckBox;
    JCheckBox proximityShearHomeCheckBox;
    JCheckBox proximityShearCutCheckBox;
    JCheckBox proximityToolInCheckBox;
    JCheckBox proximityToolOutCheckbox;
    JCheckBox proximityHeadLimitCheckBox;
    JCheckBox proximityHeadCwCheckBox;
    JCheckBox proximityHeadCcwCheckBox;
    JPanel buttonsPanel;
    JCheckBox buttonShearCheckBox;
    JCheckBox buttonAutoCheckBox;
    JCheckBox buttonEstopCheckBox;
    JPanel currentMonitorsPanel;
    JLabel twentyFourVRawVoltLabel;
    JLabel twentyFourVRawVoltValueLabel;
    JLabel twentyFourVRawCurrentLabel;
    JLabel twentyFourVRawCurrentValueLabel;
    JLabel aux24vVoltLabel;
    JLabel aux24vVoltValueLabel;
    JLabel aux24vCurrentLabel;
    JLabel aux24vCurrentValueLabel;
    JLabel twelvevVoltLabel;
    JLabel twelvevVoltValueLabel;
    JLabel twelvevCurrentLabel;
    JLabel twelvevCurrentValueLabel;
    JLabel fivevVoltLabel;
    JLabel fivevVoltValueLabel;
    JLabel fivevCurrentLabel;
    JLabel fivevCurrentValueLabel;
    JLabel threevThreeVoltLabel;
    JLabel threevThreeVoltValueLabel;
    JLabel threevThreeCurrentLabel;
    JLabel threevThreeCurrentValueLabel;
    JLabel fGndVoltLabel;
    JLabel fGndVoltValueLabel;
    JLabel fGndCurrentLabel;
    JLabel fGndCurrentValueLabel;
    JPanel miscPanel;
    JCheckBox fuseCheckBox;
    JCheckBox twentyFourVRawCheckBox;
    JCheckBox auxTwentyFourVCheckBox;
    JLabel interfaceBoardLabel;
    JLabel firmwareVersionLabel;
    JLabel firmwareVersionValueLabel;
    JLabel bootCountLabel;
    JLabel bootCountValueLabel;
    JLabel serialNumberLabel;
    JLabel serialNumberValueLabel;
    JLabel macAddressLabel;
    JLabel macAddressValueLabel;
    JLabel ipAddressLabel;
    JLabel ipAddressValueLabel;
    JLabel subnetMaskLabel;
    JLabel subnetMaskValueLabel;
    JLabel portLabel;
    JLabel portValueLabel;
    JLabel hmiIpAddressLabel;
    JLabel hmiIpAddressValueLabel;
    JLabel hmiPortLabel;
    JLabel hmiPortValueLabel;
    JPanel statePanel;
    JLabel stateLabel;
    JLabel stateValueLabel;
    JPanel actionPanel;
    JLabel actionLabel;
    JLabel actionValueLabel;
    JButton makeShapeButton;
    JButton manualActionsButton;
    JLabel debugLogLabel;
    JScrollPane debugLogScrollPane;
    JTextArea debugTextArea;
    JDialog makeShapeJDialog;
    JPanel makeShapePanel;
    JScrollPane makeShapeScrollPane;
    JPanel makeShapeRowsPanel;
    JLabel lengthLabel;
    JTextField lengthTextField;
    JLabel bendDegreeLabel;
    JTextField bendDegreeTextField;
    JLabel directionLabel;
    JComboBox directionComboBox;
    JLabel lengthCompLabel;
    JTextField lengthCompTextField;
    JLabel bendCompLabel;
    JTextField bendCompTextField;
    JPanel addLineSendPanel;
    JButton addLineButton;
    JButton sendButton;
    JDialog manualActionsJDialog;
    JPanel manualActionsPanel;
    JButton headOutButton;
    JButton headInButton;
    JButton shearHomeButton;
    JButton shearCutButton;
    JButton toolInButton;
    JButton toolOutButton;
    JButton headLimitButton;
    JButton headCwButton;
    JButton headCcwButton;
    JButton feedForwardButton;
    JButton feedReverseButton;
    JButton eStopButton;
	// JFormDesigner - End of variables declaration  //GEN-END:variables  @formatter:on
}