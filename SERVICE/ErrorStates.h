#ifndef ERRORSTATES_H_
#define ERRORSTATES_H_

typedef enum
{
	ES_OK,
	ES_NOK,
	ES_NULL_POINTER,
	ES_OUT_OF_RANGE,
	ES_UNSUPPORTED_SENSE_Config,
	ES_UNSUPPORTED_prescaller_Config,
	ES_UNSUPPORTED_trigger_source_Config,
	ES_TIMEOUT_STATE,
	ES_BUSY_STATE
}ES_t;

#endif /* ERRORSTATES_H_ */
