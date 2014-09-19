#include "io.h"
#include "safe.h"
#include <string.h>


void readinfo(char *filename, char **mdlogfilepath, char **tdlogfilepath, char **mdserver, char **tdserver, char **mongodb_url_port, char **BrokerID, char **InvestorID, char **UserID, char **pd, char **UserProductInfo, char *(*InstrumentIDs)[], int *InstrumentNum) {
	FILE *fp = sfopen(filename, "r");
	char line[1000];
	int i = 0;
	int j = 0;
	while(fgets(line, 1000, fp)) {
		switch(i++) {
			case 0:
				*mdlogfilepath = smalloc(strlen(line));
				memcpy(*mdlogfilepath, line, strlen(line));
				(*mdlogfilepath)[strlen(line)-1] = '\0';
				break;
			case 1:
				*tdlogfilepath = smalloc(strlen(line));
				memcpy(*tdlogfilepath, line, strlen(line));
				(*tdlogfilepath)[strlen(line)-1] = '\0';
				break;
			case 2:
				*mdserver = smalloc(strlen(line));
				memcpy(*mdserver, line, strlen(line));
				(*mdserver)[strlen(line)-1] = '\0';
				break;
			case 3:
				*tdserver = smalloc(strlen(line));
				memcpy(*tdserver, line, strlen(line));
				(*tdserver)[strlen(line)-1] = '\0';
				break;
			case 4:
				*mongodb_url_port = smalloc(strlen(line));
				memcpy(*mongodb_url_port, line, strlen(line));
				(*mongodb_url_port)[strlen(line)-1] = '\0';
				break;
			case 5:
				*BrokerID= smalloc(strlen(line));
				memcpy(*BrokerID, line, strlen(line));
				(*BrokerID)[strlen(line)-1] = '\0';
				break;
			case 6:
				*InvestorID= smalloc(strlen(line));
				memcpy(*InvestorID, line, strlen(line));
				(*InvestorID)[strlen(line)-1] = '\0';
				break;
			case 7:
				*UserID= smalloc(strlen(line));
				memcpy(*UserID, line, strlen(line));
				(*UserID)[strlen(line)-1] = '\0';
				break;
			case 8:
				*pd = smalloc(strlen(line));
				memcpy(*pd, line, strlen(line));
				(*pd)[strlen(line)-1] = '\0';
				break;
			case 9:
				*UserProductInfo = smalloc(strlen(line));
				memcpy(*UserProductInfo, line, strlen(line));
				(*UserProductInfo)[strlen(line)-1] = '\0';
				break;
			default:
				(*InstrumentIDs)[j] = smalloc(strlen(line));
				memcpy((*InstrumentIDs)[j], line, strlen(line));
				(*InstrumentIDs)[j][strlen(line)-1] = '\0';
				j++;
				break;
		}
	}
	*InstrumentNum = j;
	fclose(fp);
}
