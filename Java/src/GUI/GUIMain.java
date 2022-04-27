package GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


/* Help from :
- https://www.guru99.com/java-swing-gui.html
- https://stackoverflow.com/questions/2536873/how-can-i-set-size-of-a-button
- https://docs.oracle.com/javase/tutorial/uiswing/events/actionlistener.html
- https://stackoverflow.com/questions/5911565/how-to-add-multiple-actionlisteners-for-multiple-buttons-in-java-swing
- https://stackoverflow.com/questions/34250434/jframe-setdefaultcloseoperation-not-working
*/

public class GUIMain extends JFrame{
	JPanel buttonsPanel;
	JButton butDefrag;
	JButton butVerif;
	JLabel outputLabel;
	
	public static void main(String args[]){
		GUIMain window = new GUIMain("OSCratch management tool");
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setSize(415,200);
		
		window.setVisible(true);
    }

	public GUIMain (String title) {
		super(title);
		
		setLayout(new FlowLayout());		
		
		// Creating the main panel
		buttonsPanel = new JPanel();

		butDefrag = new JButton("Défragmentation");
		butDefrag.setPreferredSize(new Dimension(200, 100));
		butDefrag.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				// Code défragmentation
				System.out.println("Défragmentation");
				
				
				// Retour dans outputLabel
				outputLabel.setText("Défragmentation");
			}
		});
		
		butVerif = new JButton("Vérification");
		butVerif.setPreferredSize(new Dimension(200, 100));
		butVerif.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				// Code vérification
				System.out.println("Vérification");
				
				// Retour dans outputLabel
				outputLabel.setText("Vérification");
			}
		});
		
		buttonsPanel.add(butDefrag);
		buttonsPanel.add(butVerif);

		
		//Creating an output label
		outputLabel = new JLabel("");
		
		
		// Adding components to the frame
		add(BorderLayout.CENTER, buttonsPanel);
		add(BorderLayout.SOUTH, outputLabel);
	}
	
	
	public void windowClosing(WindowEvent e) {
	        dispose();
	        System.exit(0);
	}
	public void windowOpened(WindowEvent e) {}
    public void windowActivated(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
    public void windowDeactivated(WindowEvent e) {}
    public void windowClosed(WindowEvent e) {}
}