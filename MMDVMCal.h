/*
 *   Copyright (C) 2015,2016,2017 by Jonathan Naylor G4KLX
 *   Copyright (C) 2017,2018 by Andy Uribe CA6JAU
 *   Copyright (C) 2018 by Bryan Biedenkapp N2PLL
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if !defined(MMDVMCAL_H)
#define	MMDVMCAL_H

#include "SerialController.h"
#include "Console.h"
#include "BERCal.h"

#include <cstring>
#include <cstdlib>

enum RESP_TYPE_MMDVM {
	RTM_OK,
	RTM_TIMEOUT,
	RTM_ERROR
};

enum HW_TYPE {
	HWT_MMDVM,
	HWT_MMDVM_HS
};

enum MMDVM_STATE {
  STATE_DMR       = 2,
  STATE_P25       = 4,
  STATE_NXDNCAL1K = 91,
  STATE_DMRDMO1K  = 92,
  STATE_P25CAL1K  = 93,
  STATE_DMRCAL1K  = 94,
  STATE_LFCAL     = 95,
  STATE_RSSICAL   = 96,
  STATE_DMRCAL    = 98,
  STATE_DSTARCAL  = 99
};

class CMMDVMCal {
public:
	CMMDVMCal(const std::string& port);
	~CMMDVMCal();

	int run();

private:
	CSerialController m_serial;
	CConsole          m_console;
	CBERCal           m_ber;
	bool              m_transmit;
	bool              m_carrier;
	float             m_txLevel;
	float             m_rxLevel;
	int               m_txDCOffset;
	int               m_rxDCOffset;
	bool              m_txInvert;
	bool              m_rxInvert;
	bool              m_pttInvert;
	unsigned int      m_frequency;
	unsigned int      m_startfrequency;
	float             m_power;
	MMDVM_STATE       m_mode;
	bool              m_duplex;
	unsigned char*    m_buffer;
	unsigned int      m_length;
	unsigned int      m_offset;
	HW_TYPE           m_hwType;
	bool              m_dmrEnabled;
	bool              m_p25Enabled;

	void displayHelp_MMDVM();
	void displayHelp_MMDVM_HS();
	void loop_MMDVM();
	void loop_MMDVM_HS();
	bool setTransmit();
	bool setTXLevel(int incr);
	bool setRXLevel(int incr);
	bool setTXDCOffset(int incr);
	bool setRXDCOffset(int incr);
	bool setTXInvert();
	bool setRXInvert();
	bool setPTTInvert();
	bool setFreq(int incr);
	bool setPower(int incr);
	bool setCarrier();
	bool setEnterFreq();
	bool setDMRDeviation();
	bool setLowFrequencyCal();
	bool setDMRCal1K();
	bool setDMRDMO1K();
	bool setP25Cal1K();
	bool setNXDNCal1K();
	bool setDMRBER();
	bool setP25BER();
	bool setDSTAR();
	bool setRSSI();

	bool initModem();
	void displayModem(const unsigned char* buffer, unsigned int length);
	bool writeConfig(float txlevel);
	void sleep(unsigned int ms);
	bool setFrequency();
	RESP_TYPE_MMDVM getResponse();
};

#endif
