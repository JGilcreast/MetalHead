import java.awt.*;
import javax.swing.*;
import javax.swing.table.*;
import com.intellij.uiDesigner.core.*;
/*
 * Created by JFormDesigner on Mon Jan 27 20:54:17 PST 2025
 */



/**
 * @author Connor
 */
public class MainPanel extends JPanel {
    public MainPanel() {
        initComponents();
    }

    private void initComponents() {
        // JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents  @formatter:off
        // Generated using JFormDesigner Educational license - Connor McMillan
        tabbedPane1 = new JTabbedPane();
        scrollPane1 = new JScrollPane();
        table1 = new JTable();
        scrollPane2 = new JScrollPane();
        table2 = new JTable();
        panel1 = new JPanel();
        panel2 = new JPanel();
        panel3 = new JPanel();
        panel4 = new JPanel();
        button8 = new JButton();
        button7 = new JButton();
        button6 = new JButton();
        button5 = new JButton();
        button4 = new JButton();
        button3 = new JButton();
        button2 = new JButton();
        button1 = new JButton();

        //======== this ========
        setPreferredSize(new Dimension(1200, 720));
        setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));

        //======== tabbedPane1 ========
        {
            tabbedPane1.setPreferredSize(new Dimension(800, 720));

            //======== scrollPane1 ========
            {

                //---- table1 ----
                table1.setModel(new DefaultTableModel(
                    new Object[][] {
                        {"", "", "", "", null},
                        {null, null, null, "", null},
                        {null, null, null, null, null},
                        {null, null, null, null, null},
                        {null, null, null, null, null},
                        {null, null, null, null, null},
                        {null, null, null, null, null},
                        {null, null, null, null, null},
                        {null, null, null, null, null},
                        {null, null, null, null, null},
                    },
                    new String[] {
                        "Number", "Length", "Angle", "Bend Compensation", "Direction"
                    }
                ) {
                    Class<?>[] columnTypes = new Class<?>[] {
                        Object.class, Object.class, Object.class, String.class, String.class
                    };
                    @Override
                    public Class<?> getColumnClass(int columnIndex) {
                        return columnTypes[columnIndex];
                    }
                });
                {
                    TableColumnModel cm = table1.getColumnModel();
                    cm.getColumn(4).setCellEditor(new DefaultCellEditor(
                        new JComboBox(new DefaultComboBoxModel(new String[] {
                            "CW",
                            "CCW"
                        }))));
                }
                scrollPane1.setViewportView(table1);
            }
            tabbedPane1.addTab("Manual Receipe", scrollPane1);

            //======== scrollPane2 ========
            {

                //---- table2 ----
                table2.setModel(new DefaultTableModel(
                    new Object[][] {
                        {null, null},
                        {null, null},
                    },
                    new String[] {
                        "ID", "Name"
                    }
                ) {
                    Class<?>[] columnTypes = new Class<?>[] {
                        String.class, Object.class
                    };
                    @Override
                    public Class<?> getColumnClass(int columnIndex) {
                        return columnTypes[columnIndex];
                    }
                });
                scrollPane2.setViewportView(table2);
            }
            tabbedPane1.addTab("Preset Receipe", scrollPane2);

            //======== panel1 ========
            {
                panel1.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));
            }
            tabbedPane1.addTab("Diagnostics", panel1);

            //======== panel2 ========
            {
                panel2.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));
            }
            tabbedPane1.addTab("Settings", panel2);

            //======== panel3 ========
            {
                panel3.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));
            }
            tabbedPane1.addTab("About", panel3);
        }
        add(tabbedPane1, new GridConstraints(0, 0, 1, 1,
            GridConstraints.ANCHOR_NORTHWEST, GridConstraints.FILL_BOTH,
            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
            null, null, null));

        //======== panel4 ========
        {
            panel4.setLayout(new GridLayoutManager(8, 1, new Insets(0, 0, 0, 0), -1, -1));

            //---- button8 ----
            button8.setText("Pause");
            button8.setFont(new Font("Inter", Font.BOLD, 16));
            panel4.add(button8, new GridConstraints(0, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, new Dimension(125, 75), null));

            //---- button7 ----
            button7.setText("Infeed");
            button7.setFont(new Font("Inter", Font.BOLD, 16));
            panel4.add(button7, new GridConstraints(1, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, new Dimension(125, 75), null));

            //---- button6 ----
            button6.setText("Run");
            button6.setFont(new Font("Inter", Font.BOLD, 16));
            panel4.add(button6, new GridConstraints(2, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, new Dimension(125, 75), null));

            //---- button5 ----
            button5.setText("Key");
            button5.setFont(new Font("Inter", Font.BOLD, 16));
            panel4.add(button5, new GridConstraints(3, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, new Dimension(125, 75), null));

            //---- button4 ----
            button4.setText("Shear");
            button4.setFont(new Font("Inter", Font.BOLD, 16));
            panel4.add(button4, new GridConstraints(4, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, new Dimension(125, 75), null));

            //---- button3 ----
            button3.setText("Comp");
            button3.setFont(new Font("Inter", Font.BOLD, 16));
            panel4.add(button3, new GridConstraints(5, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, new Dimension(125, 75), null));

            //---- button2 ----
            button2.setText("Error");
            button2.setFont(new Font("Inter", Font.BOLD, 16));
            panel4.add(button2, new GridConstraints(6, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, new Dimension(125, 75), null));

            //---- button1 ----
            button1.setText("Screen Off");
            button1.setFont(new Font("Inter", Font.BOLD, 16));
            panel4.add(button1, new GridConstraints(7, 0, 1, 1,
                GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                null, new Dimension(125, 75), null));
        }
        add(panel4, new GridConstraints(0, 1, 1, 1,
            GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
            null, null, null));
        // JFormDesigner - End of component initialization  //GEN-END:initComponents  @formatter:on
    }

    // JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables  @formatter:off
    // Generated using JFormDesigner Educational license - Connor McMillan
    private JTabbedPane tabbedPane1;
    private JScrollPane scrollPane1;
    private JTable table1;
    private JScrollPane scrollPane2;
    private JTable table2;
    private JPanel panel1;
    private JPanel panel2;
    private JPanel panel3;
    private JPanel panel4;
    private JButton button8;
    private JButton button7;
    private JButton button6;
    private JButton button5;
    private JButton button4;
    private JButton button3;
    private JButton button2;
    private JButton button1;
    // JFormDesigner - End of variables declaration  //GEN-END:variables  @formatter:on
}
