#ifndef CSerial_H
#define CSerial_H

class CSerial
{
	
	public:

	    void startSerial();
	    char readChar() const;

    protected:

		static int set_interface_attribs(int fd, int speed, int parity);
		static void set_blocking (int fd, int should_block);

		int fd;

};

#endif