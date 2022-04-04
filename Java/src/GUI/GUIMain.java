package GUI;

import javax.swing.*;
import java.awt.*;


/* Help from :
- https://www.guru99.com/java-swing-gui.html
- https://stackoverflow.com/questions/2536873/how-can-i-set-size-of-a-button


*/

public class GUIMain {
	public static void main(String args[]){
		
		// Creating the frame
		JFrame frame = new JFrame("OSCratch management tool");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(415,200);
		
		
		// Creating the main panel
		JPanel buttonsPanel = new JPanel();
		   
		JButton button1 = new JButton("Défragmentation");
		button1.setPreferredSize(new Dimension(200, 100));
		JButton button2 = new JButton("Vérification");
		button2.setPreferredSize(new Dimension(200, 100));
		
		buttonsPanel.add(button1);
		buttonsPanel.add(button2);
		
		
		//Creating an output label
		JLabel outputLabel = new JLabel("");
		
		
		// Adding components to the frame
		frame.getContentPane().add(BorderLayout.CENTER, buttonsPanel);
		frame.getContentPane().add(BorderLayout.SOUTH, outputLabel);
		
		frame.setVisible(true);
    }
}