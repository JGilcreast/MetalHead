# Edit FMXL Files
To edit fmxl files with Scene Builder, you must install Scene Builder.
Do not use the IntelliJ IDEA plugin. You do not have access to the
library manager.
1. Download [Scene Builder](https://gluonhq.com/products/scene-builder/) and install it
2. Click on the dropdown menu with the gear icon
3. Click on JAR/FXML Manager
4. Click on Search repositories
5. Search and install the following libraries:
   * org.kordcamp.ikonli:ikonli-boxicons-pack:12.3.1
   * org.kordcamp.ikonli:ikonli-javafx:12.3.1
6. Click on File > Open and select metalhead-hmi.fmxl

You should not get an exception/error from Scene Builder.

# FontIcon - Selection Start & Selection End
Scene Builder will default **Selection Start** and **Selection End** to -1
when adding them onto the canvas. Make sure to set these to 0. Not doing so
will cause Scene Builder to run into an exception, and you will not be able
to save your work. If this happens, you will also not be able to open the FMXL
file again. To overcome this issue, open the FMXL file with a text editor and 
make sure all SelectionEnd and ElectionStart keys are set to 0. Save the 
changes, and you should be able to open it with Scene Builder again. 