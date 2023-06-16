/*!Begin Snippet:file*/

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * This class is the interface startup class of the milk system.
 *
 * @author ydecube
 * @version 1.1.0
 * @see Controller
 */
public class BrightFreshMilkSystem extends Application {

    /*
     * Loads the interface file and display the window.
     */
    @Override
    public void start(Stage primaryStage) throws Exception{

        Parent root = FXMLLoader.load(getClass().getResource("system.fxml"));
        primaryStage.setTitle("Bright Fresh Milk System");
        primaryStage.setScene(new Scene(root, 745.0, 580.0));
        primaryStage.show();
    }

    /**
     * Start project.
     *
     * @param args  String arguments.
     */
    public static void main(String[] args) {

        launch(args);
    }
}
/*!End Snippet:file*/
