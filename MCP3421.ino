#include "MCP3421.h"
#include "Wire.h"

#define MCP_Add 0xd0>>1

#define MCP_ReStart 0x80
#define MCP_ContinuousConversion 0x10
#define MCP_SingleConversion 0x00

#define MCP_12bit 0x00
#define MCP_14bit 0x04
#define MCP_16bit 0x08
#define MCP_18bit 0x0c
#define MCP_PGA1 0x00
#define MCP_PGA2 0x01
#define MCP_PGA4 0x02
#define MCP_PGA8 0x03

#define MCP_Resolution MCP_18bit
#define MCP_PGA MCP_PGA8

union _MCPData {
	int32_t Data;
	struct {
		uint8_t Lower :8;
		uint8_t Middle :8;
		uint8_t Upper :8;
		uint8_t Reserved :8;
	};
} MCPData;

void MCP_Init() {
	Wire.beginTransmission(MCP_Add);
	Wire.write(MCP_ContinuousConversion | MCP_Resolution | MCP_PGA);
	Wire.endTransmission(true);
}

double MCP_GetDate() {
	Wire.requestFrom(MCP_Add, 3, true);
	MCPData.Upper = Wire.read();
	MCPData.Middle = Wire.read();
	MCPData.Lower = Wire.read();
	//data is negative
	if (MCPData.Upper & 0x02) {
		MCPData.Data = ~MCPData.Data;
		MCPData.Reserved = 0;
		MCPData.Upper &= 0x03;	//Reserved last two bit
		MCPData.Data++;
		return MCP_Fit(-MCPData.Data);
	}
	//data is positive
	else {
		return MCP_Fit(MCPData.Data);
	}
}

double MCP_Fit(double x) {
	return 0.00006170108886838811 * x + 0.01417074171674996;
}
