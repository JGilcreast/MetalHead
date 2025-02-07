import java.awt.*;
import javax.swing.*;
import com.intellij.uiDesigner.core.*;
//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        //TIP Press <shortcut actionId="ShowIntentionActions"/> with your caret at the highlighted text
        // to see how IntelliJ IDEA suggests fixing it.
        System.out.printf("Hello and welcome!");

        for (int i = 1; i <= 5; i++) {
            //TIP Press <shortcut actionId="Debug"/> to start debugging your code. We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/> breakpoint
            // for you, but you can always add more by pressing <shortcut actionId="ToggleLineBreakpoint"/>.
            System.out.println("i = " + i);
        }
    }

    private void initComponents() {
        // JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents  @formatter:off
        // Generated using JFormDesigner Educational license - Connor McMillan
        tabbedPane1 = new JTabbedPane();
        panel1 = new JPanel();
        scrollPane1 = new JScrollPane();
        table1 = new JTable();
        panel2 = new JPanel();
        scrollPane2 = new JScrollPane();
        table2 = new JTable();
        panel3 = new JPanel();
        panel4 = new JPanel();
        panel5 = new JPanel();
        panel6 = new JPanel();

        //======== this ========
        setPreferredSize(new Dimension(1200, 720));
        setLayout(new GridLayoutManager(3, 3, new Insets(0, 0, 0, 0), -1, -1));

        //======== tabbedPane1 ========
        {

            //======== panel1 ========
            {
                panel1.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));

                //======== scrollPane1 ========
                {
                    scrollPane1.setViewportView(table1);
                }
                panel1.add(scrollPane1, new GridConstraints(0, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
            }
            tabbedPane1.addTab("Manual Receipe", panel1);

            //======== panel2 ========
            {
                panel2.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));

                //======== scrollPane2 ========
                {
                    scrollPane2.setViewportView(table2);
                }
                panel2.add(scrollPane2, new GridConstraints(0, 0, 1, 1,
                    GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
                    null, null, null));
            }
            tabbedPane1.addTab("Preset Receipe", panel2);

            //======== panel3 ========
            {
                panel3.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));
            }
            tabbedPane1.addTab("Diagnostics", panel3);

            //======== panel4 ========
            {
                panel4.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));
            }
            tabbedPane1.addTab("Settings", panel4);

            //======== panel5 ========
            {
                panel5.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));
            }
            tabbedPane1.addTab("About", panel5);
        }
        add(tabbedPane1, new GridConstraints(0, 0, 1, 1,
            GridConstraints.ANCHOR_NORTHWEST, GridConstraints.FILL_BOTH,
            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
            null, null, null));

        //======== panel6 ========
        {
            panel6.setLayout(new GridLayoutManager(8, 1, new Insets(0, 0, 0, 0), -1, -1));
        }
        add(panel6, new GridConstraints(0, 1, 1, 1,
            GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH,
            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
            GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW,
            null, null, null));
        // JFormDesigner - End of component initialization  //GEN-END:initComponents  @formatter:on
    }

    // JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables  @formatter:off
    // Generated using JFormDesigner Educational license - Connor McMillan
    private JTabbedPane tabbedPane1;
    private JPanel panel1;
    private JScrollPane scrollPane1;
    private JTable table1;
    private JPanel panel2;
    private JScrollPane scrollPane2;
    private JTable table2;
    private JPanel panel3;
    private JPanel panel4;
    private JPanel panel5;
    private JPanel panel6;
    // JFormDesigner - End of variables declaration  //GEN-END:variables  @formatter:on
}