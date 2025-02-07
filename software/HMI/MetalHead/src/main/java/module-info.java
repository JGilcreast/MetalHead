module com.github.jgilcreast.metalhead {
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires atlantafx.base;

    opens com.github.jgilcreast.metalhead.hmi to javafx.fxml;
    exports com.github.jgilcreast.metalhead.hmi;
}