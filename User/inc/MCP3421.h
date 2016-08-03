/*
 * MCP3421.h
 *
 *  Created on: 2016年7月31日
 *      Author: Romeli
 */

#ifndef MCP3421_H_
#define MCP3421_H_

void MCP_Init();
double MCP_GetDate();
double MCP_Fit(double x);

double MCP_Now;

#endif /* MCP3421_H_ */
