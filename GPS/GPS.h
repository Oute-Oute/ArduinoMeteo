class GPS {
	private:
		int count;
	public:
		unsigned char buffer[100];
		void clearBufferArray();
		void GetGPS_msg();
		bool Test_Synchro_GPS(char* result[]);
		void Choix_Msg_NMEA(char nmea);
		void Parser(unsigned char buffer[100]);
};