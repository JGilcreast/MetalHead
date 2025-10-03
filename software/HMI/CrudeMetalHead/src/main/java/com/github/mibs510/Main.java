package com.github.mibs510;

import com.formdev.flatlaf.themes.FlatMacDarkLaf;
import com.intellij.uiDesigner.core.*;
import com.jgoodies.forms.factories.*;
import com.jgoodies.forms.layout.*;
import net.miginfocom.layout.CC;
import net.miginfocom.swing.MigLayout;
import com.formdev.flatlaf.*;
import com.github.mibs510.StatusIndicatorsOuterClass.StatusIndicators;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class Main {
    public static void main(String[] args) {
        Main main = new Main();
        FlatMacDarkLaf.setup();
        main.initComponents();
        main.mainFrame.setVisible(true);

        try {
            byte[] buffer = new byte [1024];
            DatagramSocket socket = new DatagramSocket(3682);
            while (true) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);

                byte[] data = new byte[packet.getLength()];
                System.arraycopy(packet.getData(), packet.getOffset(), data, 0, packet.getLength());

                try {
                    StatusIndicators statusIndicators = StatusIndicators.parseFrom(data);
                    main.solenoidShearCutCheckBox.setSelected(statusIndicators.getShearCut());
                    main.solenoidShearHomeCheckBox.setSelected(statusIndicators.getShearHome());
                    main.solenoidToolOutCheckBox.setSelected(statusIndicators.getToolOut());
                    main.solenoidToolInCheckBox.setSelected(statusIndicators.getToolIn());
                    main.solenoidFeedForwardCheckBox.setSelected(statusIndicators.getFeedForward());
                    main.solenoidFeedReverseCheckBox.setSelected(statusIndicators.getFeedReverse());
                    main.solenoidHeadCwCheckBox.setSelected(statusIndicators.getHeadCw());
                    main.solenoidHeadCcwCheckBox.setSelected(statusIndicators.getHeadCcw());
                    main.solenoidHeadOutCheckBox.setSelected(statusIndicators.getHeadOut());
                    main.solenoidHeadInCheckBox.setSelected(statusIndicators.getHeadIn());
                    main.encoderFeedSetCheckBox.setSelected(statusIndicators.getEncoderFeedSet());
                    main.encoderFeedResetCheckBox.setSelected(statusIndicators.getEncoderFeedReset());
                    main.encoderBendSetCheckBox.setSelected(statusIndicators.getEncoderBendSet());
                    main.encoderBendResetCheckBox.setSelected(statusIndicators.getEncoderBendReset());
                    main.proximityHeadOutCheckBox.setSelected(statusIndicators.getProximityHeadOut());
                    main.proximityHeadInCheckBox.setSelected(statusIndicators.getProximityHeadIn());
                    main.proximityShearHomeCheckBox.setSelected(statusIndicators.getProximityShearHome());
                    main.proximityShearCutCheckBox.setSelected(statusIndicators.getProximityShearCut());
                    main.proximityToolInCheckBox.setSelected(statusIndicators.getProximityToolIn());
                    main.proximityToolOutCheckbox.setSelected(statusIndicators.getProximityToolOut());
                    main.buttonShearCheckBox.setSelected(statusIndicators.getShearButton());
                    main.proximityHeadLimitCheckBox.setSelected(statusIndicators.getProximityHeadLimit());
                    main.proximityHeadCwCheckBox.setSelected(statusIndicators.getProximityHeadCw());
                    main.proximityHeadCcwCheckBox.setSelected(statusIndicators.getProximityHeadCcw());
                    main.buttonAutoCheckBox.setSelected(statusIndicators.getAutoButton());
                    main.buttonEstopCheckBox.setSelected(statusIndicators.getEStop());
                    main.fuseCheckBox.setSelected(statusIndicators.getFuse());
                    main.twentyFourVRawCheckBox.setSelected(statusIndicators.getVraw24());
                    main.auxTwentyFourVCheckBox.setSelected(statusIndicators.getAux24V());
                    main.encoderFeedCountValueLabel.setText(String.format("%d", statusIndicators.getEncoderFeedCount()));
                    main.encoderBendCountValueLabel.setText(String.format("%d", statusIndicators.getEncoderBendCount()));
                    main.twentyFourVRawVoltValueLabel.setText(Float.toString(statusIndicators.getTwentyFourVrawBusVoltage()));
                    main.twentyFourVRawCurrentValueLabel.setText(Float.toString(statusIndicators.getTwentyFourVrawBusCurrent()));
                    main.aux24vVoltValueLabel.setText(Float.toString(statusIndicators.getAuxTwentyFourVBusVoltage()));
                    main.aux24vCurrentValueLabel.setText(Float.toString(statusIndicators.getAuxTwentyFourVBusCurrent()));
                    main.twelvevVoltValueLabel.setText(Float.toString(statusIndicators.getTwelveVBusVoltage()));
                    main.twelvevCurrentValueLabel.setText(Float.toString(statusIndicators.getTwelveVBusCurrent()));
                    main.fivevVoltValueLabel.setText(Float.toString(statusIndicators.getFiveVBusVoltage()));
                    main.fivevCurrentValueLabel.setText(Float.toString(statusIndicators.getFiveVBusCurrent()));
                    main.threevThreeVoltValueLabel.setText(Float.toString(statusIndicators.getThreeVThreeVBusVoltage()));
                    main.threevThreeCurrentValueLabel.setText(Float.toString(statusIndicators.getThreeVThreeVBusCurrent()));
                    main.fGndVoltValueLabel.setText(Float.toString(statusIndicators.getFGndBusVoltage()));
                    main.fGndCurrentValueLabel.setText(Float.toString(statusIndicators.getFGndBusCurrent()));
                } catch (IOException e) {
                    System.err.println("IOException: " + e.getMessage());
                }


            }
        } catch (SocketException e) {
            System.err.println("SocketException: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("IOException: " + e.getMessage());
        }
    }

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents  @formatter:off
        // Generated using JFormDesigner Educational license - Connor McMillan
        mainFrame = new JFrame();
        statusIndicatorsLabel = new JLabel();
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
        sendShapePanel = new JPanel();
        sendShapeButton = new JButton();
        actionsButtonPanel = new JPanel();
        actionsButton = new JButton();

        //======== mainFrame ========
        {
            mainFrame.setTitle("MetalHead HMI - Crude Edition");
            var mainFrameContentPane = mainFrame.getContentPane();
            mainFrameContentPane.setLayout(new GridLayoutManager(6, 8, new Insets(0, 0, 0, 0), -1, -1));

            //---- statusIndicatorsLabel ----
            statusIndicatorsLabel.setText("Status Indicators");
            statusIndicatorsLabel.setFont(new Font("Inter", Font.BOLD, 26));
            mainFrameContentPane.add(statusIndicatorsLabel, new GridConstraints(0, 2, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //---- solenoidsLabel ----
            solenoidsLabel.setText("Solenoids");
            solenoidsLabel.setFont(new Font("Inter", Font.BOLD, 20));
            mainFrameContentPane.add(solenoidsLabel, new GridConstraints(1, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //---- encodersLabel ----
            encodersLabel.setText("Encoders");
            encodersLabel.setFont(new Font("Inter", Font.BOLD, 20));
            mainFrameContentPane.add(encodersLabel, new GridConstraints(1, 1, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //---- proximitySensorLabel ----
            proximitySensorLabel.setText("Proximity Sensors");
            proximitySensorLabel.setFont(new Font("Inter", Font.BOLD, 20));
            mainFrameContentPane.add(proximitySensorLabel, new GridConstraints(1, 2, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //---- buttonsLabel ----
            buttonsLabel.setText("Buttons");
            buttonsLabel.setFont(new Font("Inter", Font.BOLD, 20));
            mainFrameContentPane.add(buttonsLabel, new GridConstraints(1, 3, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //---- currentMonitorLabel ----
            currentMonitorLabel.setText("Current Monitors");
            currentMonitorLabel.setFont(new Font("Inter", Font.BOLD, 20));
            mainFrameContentPane.add(currentMonitorLabel, new GridConstraints(1, 4, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //---- miscLabel ----
            miscLabel.setText("Misc");
            miscLabel.setFont(new Font("Inter", Font.BOLD, 20));
            mainFrameContentPane.add(miscLabel, new GridConstraints(1, 5, 1, 1,
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
            mainFrameContentPane.add(solenoidsPanel, new GridConstraints(2, 0, 1, 1,
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
            mainFrameContentPane.add(encodersPanel, new GridConstraints(2, 1, 1, 1,
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
            mainFrameContentPane.add(proximitySensorsPanel, new GridConstraints(2, 2, 1, 1,
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
            mainFrameContentPane.add(buttonsPanel, new GridConstraints(2, 3, 1, 1,
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
            mainFrameContentPane.add(currentMonitorsPanel, new GridConstraints(2, 4, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //======== miscPanel ========
            {
                miscPanel.setLayout(new GridLayoutManager(8, 2, new Insets(0, 0, 0, 0), -1, -1));

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

                //---- bootCountLabel ----
                bootCountLabel.setText("Boot Count:");
                miscPanel.add(bootCountLabel, new GridConstraints(3, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
                miscPanel.add(bootCountValueLabel, new GridConstraints(3, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- serialNumberLabel ----
                serialNumberLabel.setText("Serial Number:");
                miscPanel.add(serialNumberLabel, new GridConstraints(4, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
                miscPanel.add(serialNumberValueLabel, new GridConstraints(4, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- macAddressLabel ----
                macAddressLabel.setText("MAC Address:");
                miscPanel.add(macAddressLabel, new GridConstraints(5, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
                miscPanel.add(macAddressValueLabel, new GridConstraints(5, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- ipAddressLabel ----
                ipAddressLabel.setText("IP Address:");
                miscPanel.add(ipAddressLabel, new GridConstraints(6, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
                miscPanel.add(ipAddressValueLabel, new GridConstraints(6, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));

                //---- subnetMaskLabel ----
                subnetMaskLabel.setText("Subnet Mask:");
                miscPanel.add(subnetMaskLabel, new GridConstraints(7, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
                miscPanel.add(subnetMaskValueLabel, new GridConstraints(7, 1, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
            }
            mainFrameContentPane.add(miscPanel, new GridConstraints(2, 5, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //======== sendShapePanel ========
            {
                sendShapePanel.setLayout(new GridLayoutManager(1, 1, new Insets(0, 0, 10, 0), -1, -1));

                //---- sendShapeButton ----
                sendShapeButton.setText("Send Shape");
                sendShapePanel.add(sendShapeButton, new GridConstraints(0, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
            }
            mainFrameContentPane.add(sendShapePanel, new GridConstraints(4, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));

            //======== actionsButtonPanel ========
            {
                actionsButtonPanel.setLayout(new GridLayoutManager(1, 1, new Insets(0, 0, 10, 0), -1, -1));

                //---- actionsButton ----
                actionsButton.setText("Actions");
                actionsButtonPanel.add(actionsButton, new GridConstraints(0, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
            }
            mainFrameContentPane.add(actionsButtonPanel, new GridConstraints(4, 2, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, null, null));
            mainFrame.pack();
            mainFrame.setLocationRelativeTo(mainFrame.getOwner());
        }
		// JFormDesigner - End of component initialization  //GEN-END:initComponents  @formatter:on
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables  @formatter:off
    // Generated using JFormDesigner Educational license - Connor McMillan
    private JFrame mainFrame;
    private JLabel statusIndicatorsLabel;
    private JLabel solenoidsLabel;
    private JLabel encodersLabel;
    private JLabel proximitySensorLabel;
    private JLabel buttonsLabel;
    private JLabel currentMonitorLabel;
    private JLabel miscLabel;
    private JPanel solenoidsPanel;
    private JCheckBox solenoidShearCutCheckBox;
    private JCheckBox solenoidShearHomeCheckBox;
    private JCheckBox solenoidToolOutCheckBox;
    private JCheckBox solenoidToolInCheckBox;
    private JCheckBox solenoidFeedForwardCheckBox;
    private JCheckBox solenoidFeedReverseCheckBox;
    private JCheckBox solenoidHeadCwCheckBox;
    private JCheckBox solenoidHeadCcwCheckBox;
    private JCheckBox solenoidHeadOutCheckBox;
    private JCheckBox solenoidHeadInCheckBox;
    private JPanel encodersPanel;
    private JCheckBox encoderFeedSetCheckBox;
    private JCheckBox encoderFeedResetCheckBox;
    private JCheckBox encoderBendSetCheckBox;
    private JCheckBox encoderBendResetCheckBox;
    private JLabel encoderFeedCountLabel;
    private JLabel encoderFeedCountValueLabel;
    private JLabel encoderBendCountLabel;
    private JLabel encoderBendCountValueLabel;
    private JPanel proximitySensorsPanel;
    private JCheckBox proximityHeadOutCheckBox;
    private JCheckBox proximityHeadInCheckBox;
    private JCheckBox proximityShearHomeCheckBox;
    private JCheckBox proximityShearCutCheckBox;
    private JCheckBox proximityToolInCheckBox;
    private JCheckBox proximityToolOutCheckbox;
    private JCheckBox proximityHeadLimitCheckBox;
    private JCheckBox proximityHeadCwCheckBox;
    private JCheckBox proximityHeadCcwCheckBox;
    private JPanel buttonsPanel;
    private JCheckBox buttonShearCheckBox;
    private JCheckBox buttonAutoCheckBox;
    private JCheckBox buttonEstopCheckBox;
    private JPanel currentMonitorsPanel;
    private JLabel twentyFourVRawVoltLabel;
    private JLabel twentyFourVRawVoltValueLabel;
    private JLabel twentyFourVRawCurrentLabel;
    private JLabel twentyFourVRawCurrentValueLabel;
    private JLabel aux24vVoltLabel;
    private JLabel aux24vVoltValueLabel;
    private JLabel aux24vCurrentLabel;
    private JLabel aux24vCurrentValueLabel;
    private JLabel twelvevVoltLabel;
    private JLabel twelvevVoltValueLabel;
    private JLabel twelvevCurrentLabel;
    private JLabel twelvevCurrentValueLabel;
    private JLabel fivevVoltLabel;
    private JLabel fivevVoltValueLabel;
    private JLabel fivevCurrentLabel;
    private JLabel fivevCurrentValueLabel;
    private JLabel threevThreeVoltLabel;
    private JLabel threevThreeVoltValueLabel;
    private JLabel threevThreeCurrentLabel;
    private JLabel threevThreeCurrentValueLabel;
    private JLabel fGndVoltLabel;
    private JLabel fGndVoltValueLabel;
    private JLabel fGndCurrentLabel;
    private JLabel fGndCurrentValueLabel;
    private JPanel miscPanel;
    private JCheckBox fuseCheckBox;
    private JCheckBox twentyFourVRawCheckBox;
    private JCheckBox auxTwentyFourVCheckBox;
    private JLabel bootCountLabel;
    private JLabel bootCountValueLabel;
    private JLabel serialNumberLabel;
    private JLabel serialNumberValueLabel;
    private JLabel macAddressLabel;
    private JLabel macAddressValueLabel;
    private JLabel ipAddressLabel;
    private JLabel ipAddressValueLabel;
    private JLabel subnetMaskLabel;
    private JLabel subnetMaskValueLabel;
    private JPanel sendShapePanel;
    private JButton sendShapeButton;
    private JPanel actionsButtonPanel;
    private JButton actionsButton;
	// JFormDesigner - End of variables declaration  //GEN-END:variables  @formatter:on
}