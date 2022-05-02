package utils;

import java.io.IOException;
import java.io.RandomAccessFile;

import analyseFichier.AnalyseFichier;

/**
 * @author xenoswifts
 *
 */
public class Super_block {

	private int nb_fichier;
	private int nb_user;
	private int nb_block_disk;
	private int first_free_byte;
	
	
	
	public String set_super_block(RandomAccessFile i){
		try {
			
			this.nb_fichier=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			this.nb_user=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			this.nb_block_disk=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			this.first_free_byte=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			return "tout est ok!";
			
		}catch(IOException e) {
			return "Problème de lecture du super_block";
		}
		
	}
	
	public void printsb() {
		System.out.print(nb_fichier+"\n"+ nb_user+"\n"+nb_block_disk+"\n"+first_free_byte+"\n");
	}


	public int getNb_fichier() {
		return nb_fichier;
	}

	public int getNb_user() {
		return nb_user;
	}

	public int getNb_block_disk() {
		return nb_block_disk;
	}

	public int getFirst_free_byte() {
		return first_free_byte;
	}
}
