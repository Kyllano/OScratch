package GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import analyseFichier.AnalyseFichier;
import défragmentation.Defragmentation;


/* Help from :
- https://www.guru99.com/java-swing-gui.html
- https://stackoverflow.com/questions/2536873/how-can-i-set-size-of-a-button
- https://docs.oracle.com/javase/tutorial/uiswing/events/actionlistener.html
- https://stackoverflow.com/questions/5911565/how-to-add-multiple-actionlisteners-for-multiple-buttons-in-java-swing
- https://stackoverflow.com/questions/34250434/jframe-setdefaultcloseoperation-not-working
*/

public class GUIMain extends JFrame{
	private static final long serialVersionUID = 1L;
	JPanel buttonsPanel;
	JButton butDefrag;
	JButton butVerif;
	
	JLabel outputLabel;
	
	JPanel textPanel;
	JLabel indicator;
	JTextField textField;
	String diskname;
	
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
				
				// Retour dans outputLabel
				diskname = textField.getText();
				outputLabel.setText("Défragmentation : " + Defragmentation.run(diskname));
				
			}
		});

		butVerif = new JButton("Analyse");
		butVerif.setPreferredSize(new Dimension(200, 100));
		butVerif.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {

				// Retour dans outputLabel
				diskname = textField.getText();
				outputLabel.setText("Analyse : " + AnalyseFichier.run(diskname));
				
			}
		});
		
		buttonsPanel.add(butDefrag);
		buttonsPanel.add(butVerif);

		
		//Creating an output label
		outputLabel = new JLabel("");
		
		
		//Creating a text field for the disk name
		indicator = new JLabel("Nom du disque :");
		//textPanel.add(BorderLayout.WEST, indicator);
		textField = new JTextField(5);
		textField.setText("d0");
		//textPanel.add(BorderLayout.CENTER, textField);
		
		// Adding components to the frame
		add(BorderLayout.NORTH, indicator);
		add(BorderLayout.NORTH, textField);
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