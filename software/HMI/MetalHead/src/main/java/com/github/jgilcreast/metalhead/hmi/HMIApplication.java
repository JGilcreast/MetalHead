package com.github.jgilcreast.metalhead.hmi;

import atlantafx.base.theme.CupertinoDark;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.IOException;

public class HMIApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HMIApplication.class.getResource("metalhead-hmi.fxml"));
        Application.setUserAgentStylesheet(new CupertinoDark().getUserAgentStylesheet());
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("MetalHead HMI");
        stage.getIcons().add(new Image("/MH-64.png"));
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}