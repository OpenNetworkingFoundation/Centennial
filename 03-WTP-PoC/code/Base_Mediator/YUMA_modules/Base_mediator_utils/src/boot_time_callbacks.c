/*
 * boot_time_callbacks.c
 *
 *  Created on: Aug 19, 2016
 *      Author: compila
 */

#include "boot_time_callbacks.h"
#include "utils.h"
#include "y_MicrowaveModel-ObjectClasses-AirInterface.h"

static const char* cb_get_boot_time_airInterfaceCapability_typeOfEquipment(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_txFrequencyMin(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_txFrequencyMax(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_rxFrequencyMin(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_rxFrequencyMax(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_adaptiveModulationIsAvail(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_mimoIsAvail(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_mimoChannels(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_alicIsAvail(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_atpcIsAvail(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_atpcRange(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_encryptionIsAvail(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_loopBackIsAvail(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_maintenanceTimerRange(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedAlarms(val_value_t *element);

static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_supportedChannelPlan(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_duplexDistanceIsVariable(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_duplexDistance(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_autoFreqSelectIsAvail(val_value_t *element);

static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_channelBandwidth(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_modulationScheme(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_informationRate(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_txPowerMin(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_txPowerMax(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_rxThreshold(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_amUpshiftLevel(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_amDownshiftLevel(val_value_t *element);
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_xpicIsAvail(val_value_t *element);

static const char* cb_get_boot_time_airInterfaceConfiguration_problemKindSeverity(val_value_t *element);

/********************************************************************
* FUNCTION cb_get_all_air_interface_pac_keys
*
* Get an array representing the keys of MW_AirInterface_Pac list
*
* OUTPUTS:
* char** air_interface_pac_keys_list - an array of strings containing the list of keys
* int* num_of_keys - the number of keys found (actually the number of interfaces found)
*
* RETURNS:
*     error status
********************************************************************/
status_t cb_get_all_air_interface_pac_keys(char** air_interface_pac_keys_list, int* num_of_keys)
{
	*num_of_keys = 0;

	/*
	 * fill in the actual values for the MW_AirInterface_Pac layerProtocol list here. E.g.:
	 */

	char layerProtocol[256];
	char layerProtocolString[256];

	strcpy(layerProtocolString, "ifIndex1");
	strcpy(layerProtocol, LP_MWPS_PREFIX);
	strcat(layerProtocol, layerProtocolString);

	air_interface_pac_keys_list[*num_of_keys] = (char*) malloc(strlen(layerProtocol) + 1);
	YUMA_ASSERT(air_interface_pac_keys_list[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(air_interface_pac_keys_list[*num_of_keys], layerProtocol);

	*num_of_keys += 1;

	strcpy(layerProtocolString, "ifIndex2");
	strcpy(layerProtocol, LP_MWPS_PREFIX);
	strcat(layerProtocol, layerProtocolString);

	air_interface_pac_keys_list[*num_of_keys] = (char*) malloc(strlen(layerProtocol) + 1);
	YUMA_ASSERT(air_interface_pac_keys_list[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(air_interface_pac_keys_list[*num_of_keys], layerProtocol);

	*num_of_keys += 1;

	return NO_ERR;
}

/********************************************************************
* FUNCTION cb_get_all_supported_channel_plan_list_keys
*
* Get an array representing the keys of supportedChannelPlanList list
*
* INPUTS:
* char *air_interface_pac_key - the key of the current interface
* OUTPUTS:
* char** supported_channel_plan_list_key_entries - an array of strings containing the list of keys
* int* num_of_keys - the number of keys found on the interface
*
* RETURNS:
*     error status
********************************************************************/
status_t cb_get_all_supported_channel_plan_list_keys(const char *air_interface_pac_key, char **supported_channel_plan_list_key_entries, int *num_of_keys)
{
	*num_of_keys = 0;

	/*
	 * fill in the actual values for the supportedChannelPlanList keys here, using the air_interface_pac_key as a key for finding the relevant information E.g.:
	 */

	char supportedChannelPlan[256];

	strcpy(supportedChannelPlan, "ETSI");

	supported_channel_plan_list_key_entries[*num_of_keys] = (char*) malloc(strlen(supportedChannelPlan) + 1);
	YUMA_ASSERT(supported_channel_plan_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(supported_channel_plan_list_key_entries[*num_of_keys], supportedChannelPlan);

	*num_of_keys += 1;

	strcpy(supportedChannelPlan, "FCC");

	supported_channel_plan_list_key_entries[*num_of_keys] = (char*) malloc(strlen(supportedChannelPlan) + 1);
	YUMA_ASSERT(supported_channel_plan_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(supported_channel_plan_list_key_entries[*num_of_keys], supportedChannelPlan);

	*num_of_keys += 1;

	return NO_ERR;
}

/********************************************************************
* FUNCTION cb_get_all_transmission_mode_id_list_keys
*
* Get an array representing the keys of transmissionModeList list
*
* INPUTS:
* const char *air_interface_pac_key - the key of the current interface
* const char *supported_channel_plan_key - the key of the current supportedChannelPlanList entry
* OUTPUTS:
* char** transmission_mode_id_list_key_entries - an array of strings containing the list of keys
* int* num_of_keys - the number of keys found on the interface
*
* RETURNS:
*     error status
********************************************************************/
status_t cb_get_all_transmission_mode_id_list_keys(const char *air_interface_pac_key, const char *supported_channel_plan_key, char **transmission_mode_id_list_key_entries, int *num_of_keys)
{
	*num_of_keys = 0;

	/*
	 * fill in the actual values for the transmissionModeList keys here, using the air_interface_pac_key and supported_channel_plan_key as keys for finding the relevant information E.g.:
	 */

	char transmissionModeId[256];

	if (strcmp(supported_channel_plan_key, "ETSI") == 0)
	{
		strcpy(transmissionModeId, "script_1");

		transmission_mode_id_list_key_entries[*num_of_keys] = (char*) malloc(strlen(transmissionModeId) + 1);
		YUMA_ASSERT(transmission_mode_id_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

		strcpy(transmission_mode_id_list_key_entries[*num_of_keys], transmissionModeId);

		*num_of_keys += 1;

		strcpy(transmissionModeId, "script_2");

		transmission_mode_id_list_key_entries[*num_of_keys] = (char*) malloc(strlen(transmissionModeId) + 1);
		YUMA_ASSERT(transmission_mode_id_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

		strcpy(transmission_mode_id_list_key_entries[*num_of_keys], transmissionModeId);

		*num_of_keys += 1;
	}
	else
	{
		strcpy(transmissionModeId, "script_3");

		transmission_mode_id_list_key_entries[*num_of_keys] = (char*) malloc(strlen(transmissionModeId) + 1);
		YUMA_ASSERT(transmission_mode_id_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

		strcpy(transmission_mode_id_list_key_entries[*num_of_keys], transmissionModeId);

		*num_of_keys += 1;

		strcpy(transmissionModeId, "script_4");

		transmission_mode_id_list_key_entries[*num_of_keys] = (char*) malloc(strlen(transmissionModeId) + 1);
		YUMA_ASSERT(transmission_mode_id_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

		strcpy(transmission_mode_id_list_key_entries[*num_of_keys], transmissionModeId);

		*num_of_keys += 1;

	}
	return NO_ERR;
}

/********************************************************************
* FUNCTION cb_get_all_problem_kind_severity_list_keys
*
* Get an array representing the keys of problemKindSeverityList list
*
* INPUTS:
* char *air_interface_pac_key - the key of the current interface
* OUTPUTS:
* char** problem_kind_severity_list_key_entries - an array of strings containing the list of keys
* int* num_of_keys - the number of keys found on the interface
*
* RETURNS:
*     error status
********************************************************************/
status_t cb_get_all_problem_kind_severity_list_keys(const char *air_interface_pac_key, char **problem_kind_severity_list_key_entries, int *num_of_keys)
{
	*num_of_keys = 0;

	/*
	 * fill in the actual values for the problemKindSeverityList keys here, using the air_interface_pac_key as a key for finding the relevant information E.g.:
	 */

	char problemKindName[256];

	strcpy(problemKindName, "alarm1");

	problem_kind_severity_list_key_entries[*num_of_keys] = (char*) malloc(strlen(problemKindName) + 1);
	YUMA_ASSERT(problem_kind_severity_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(problem_kind_severity_list_key_entries[*num_of_keys], problemKindName);

	*num_of_keys += 1;

	strcpy(problemKindName, "alarm2");

	problem_kind_severity_list_key_entries[*num_of_keys] = (char*) malloc(strlen(problemKindName) + 1);
	YUMA_ASSERT(problem_kind_severity_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(problem_kind_severity_list_key_entries[*num_of_keys], problemKindName);

	*num_of_keys += 1;

	strcpy(problemKindName, "alarm3");

	problem_kind_severity_list_key_entries[*num_of_keys] = (char*) malloc(strlen(problemKindName) + 1);
	YUMA_ASSERT(problem_kind_severity_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(problem_kind_severity_list_key_entries[*num_of_keys], problemKindName);

	*num_of_keys += 1;

	strcpy(problemKindName, "alarm4");

	problem_kind_severity_list_key_entries[*num_of_keys] = (char*) malloc(strlen(problemKindName) + 1);
	YUMA_ASSERT(problem_kind_severity_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(problem_kind_severity_list_key_entries[*num_of_keys], problemKindName);

	*num_of_keys += 1;

	strcpy(problemKindName, "alarm5");

	problem_kind_severity_list_key_entries[*num_of_keys] = (char*) malloc(strlen(problemKindName) + 1);
	YUMA_ASSERT(problem_kind_severity_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(problem_kind_severity_list_key_entries[*num_of_keys], problemKindName);

	*num_of_keys += 1;

	strcpy(problemKindName, "alarm6");

	problem_kind_severity_list_key_entries[*num_of_keys] = (char*) malloc(strlen(problemKindName) + 1);
	YUMA_ASSERT(problem_kind_severity_list_key_entries[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(problem_kind_severity_list_key_entries[*num_of_keys], problemKindName);

	*num_of_keys += 1;

	return NO_ERR;
}

/********************************************************************
* FUNCTION cb_get_all_co_channel_group_id_keys
*
* Get an array representing the keys of CoChannelGroup list
*
* OUTPUTS:
* char** co_channel_group_id_keys_list - an array of strings containing the list of keys
* int* num_of_keys - the number of keys found (actually the number of co-channel groups found)
*
* RETURNS:
*     error status
********************************************************************/
status_t cb_get_all_co_channel_group_id_keys(char **co_channel_group_id_keys_list, int *num_of_keys)
{
	*num_of_keys = 0;

	/*
	 * fill in the actual values for the CoChannelGroup keys hereE.g.:
	 */

	char coChannelGroupId[256];

	strcpy(coChannelGroupId, "coChannelGroupId1");

	co_channel_group_id_keys_list[*num_of_keys] = (char*) malloc(strlen(coChannelGroupId) + 1);
	YUMA_ASSERT(co_channel_group_id_keys_list[*num_of_keys] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(co_channel_group_id_keys_list[*num_of_keys], coChannelGroupId);

	*num_of_keys += 1;

	return NO_ERR;
}

/********************************************************************
* FUNCTION cb_get_all_co_channel_group_air_interface_list_id_keys
*
* Get an array representing the leaf-list entries of airInterfaceList leaf-list
*
* INPUTS:
* char *co_channel_group_id_key - the key of the co-channel group
* OUTPUTS:
* char** co_channel_group_air_interface_list_entries - an array of strings containing the list of keys
* int* num_of_keys - the number of keys found (actually the number of interfaces found in the group)
*
* RETURNS:
*     error status
********************************************************************/
status_t cb_get_all_co_channel_group_air_interface_list_id_keys(const char *co_channel_group_id_key, char **co_channel_group_air_interface_list_entries, int *num_of_entries)
{
	*num_of_entries = 0;

	/*
	 * fill in the actual values for the CoChannelGroup keys hereE.g.:
	 */

	char coChannelGroupAirInterfaceListEntry[256];

	strcpy(coChannelGroupAirInterfaceListEntry, "LP-MWPS-TTP-ifIndex1");

	co_channel_group_air_interface_list_entries[*num_of_entries] = (char*) malloc(strlen(coChannelGroupAirInterfaceListEntry) + 1);
	YUMA_ASSERT(co_channel_group_air_interface_list_entries[*num_of_entries] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(co_channel_group_air_interface_list_entries[*num_of_entries], coChannelGroupAirInterfaceListEntry);

	*num_of_entries += 1;

	strcpy(coChannelGroupAirInterfaceListEntry, "LP-MWPS-TTP-ifIndex2");

	co_channel_group_air_interface_list_entries[*num_of_entries] = (char*) malloc(strlen(coChannelGroupAirInterfaceListEntry) + 1);
	YUMA_ASSERT(co_channel_group_air_interface_list_entries[*num_of_entries] == NULL, return ERR_INTERNAL_MEM, "Could not allocate memory!");

	strcpy(co_channel_group_air_interface_list_entries[*num_of_entries], coChannelGroupAirInterfaceListEntry);

	*num_of_entries += 1;

	return NO_ERR;
}

/********************************************************************
* FUNCTION cb_get_boot_time_element_value
*
* A general function that calls a specific callback for each attribute, depending on its name
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
const char* cb_get_boot_time_element_value(val_value_t *element)
{
	if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_typeOfEquipment) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_typeOfEquipment(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_txFrequencyMin) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_txFrequencyMin(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_txFrequencyMax) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_txFrequencyMax(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_rxFrequencyMin) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_rxFrequencyMin(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_rxFrequencyMax) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_rxFrequencyMax(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_adaptiveModulationIsAvail) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_adaptiveModulationIsAvail(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_mimoIsAvail) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_mimoIsAvail(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_mimoChannels) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_mimoChannels(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_alicIsAvail) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_alicIsAvail(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_atpcIsAvail) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_atpcIsAvail(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_atpcRange) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_atpcRange(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_encryptionIsAvail) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_encryptionIsAvail(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_loopBackIsAvail) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_loopBackIsAvail(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_maintenanceTimerRange) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_maintenanceTimerRange(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_supportedAlarms) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedAlarms(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_supportedChannelPlan) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_supportedChannelPlan(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_duplexDistanceIsVariable) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_duplexDistanceIsVariable(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_duplexDistance) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_duplexDistance(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_autoFreqSelectIsAvail) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_autoFreqSelectIsAvail(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_channelBandwidth) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_channelBandwidth(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_modulationScheme) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_modulationScheme(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_informationRate) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_informationRate(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_txPowerMin) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_txPowerMin(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_txPowerMax) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_txPowerMax(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_rxThreshold) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_rxThreshold(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_amUpshiftLevel) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_amUpshiftLevel(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_amDownshiftLevel) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_amDownshiftLevel(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_xpicIsAvail) == 0)
	{
		return cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_xpicIsAvail(element);
	}
	else if (strcmp(element->name, y_MicrowaveModel_ObjectClasses_AirInterface_N_problemKindSeverity) == 0)
	{
		return cb_get_boot_time_airInterfaceConfiguration_problemKindSeverity(element);
	}


	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_typeOfEquipment
*
* Callback function for getting the value of the typeOfEquipment leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_typeOfEquipment(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information. E.g.:
	 */

	if (strcmp(VAL_STRING(layerProtocolKey), "LP-MWPS-TTP-ifIndex1") == 0)
	{
		return "MW_type_1";
	}
	if (strcmp(VAL_STRING(layerProtocolKey), "LP-MWPS-TTP-ifIndex2") == 0)
	{
		return "MW_type_2";
	}

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_txFrequencyMin
*
* Callback function for getting the value of the txFrequencyMin leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_txFrequencyMin(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_txFrequencyMax
*
* Callback function for getting the value of the txFrequencyMax leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_txFrequencyMax(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_rxFrequencyMin
*
* Callback function for getting the value of the rxFrequencyMin leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_rxFrequencyMin(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_rxFrequencyMax
*
* Callback function for getting the value of the rxFrequencyMax leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_rxFrequencyMax(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_adaptiveModulationIsAvail
*
* Callback function for getting the value of the adaptiveModulationIsAvail leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_adaptiveModulationIsAvail(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_mimoIsAvail
*
* Callback function for getting the value of the mimoIsAvail leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_mimoIsAvail(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_mimoChannels
*
* Callback function for getting the value of the mimoChannels leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_mimoChannels(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_alicIsAvail
*
* Callback function for getting the value of the alicIsAvail leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_alicIsAvail(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_atpcIsAvail
*
* Callback function for getting the value of the atpcIsAvail leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_atpcIsAvail(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_atpcRange
*
* Callback function for getting the value of the atpcRange leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_atpcRange(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_encryptionIsAvail
*
* Callback function for getting the value of the encryptionIsAvail leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_encryptionIsAvail(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_loopBackIsAvail
*
* Callback function for getting the value of the loopBackIsAvail leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_loopBackIsAvail(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_maintenanceTimerRange
*
* Callback function for getting the value of the maintenanceTimerRange leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_maintenanceTimerRange(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedAlarms
*
* Callback function for getting the value of the supportedAlarms leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedAlarms(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find key for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey as a key to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_supportedChannelPlan
*
* Callback function for getting the value of the supportedChannelPlan leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_supportedChannelPlan(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey and supportedChannelPlanKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_duplexDistanceIsVariable
*
* Callback function for getting the value of the duplexDistanceIsVariable leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_duplexDistanceIsVariable(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey and supportedChannelPlanKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_duplexDistance
*
* Callback function for getting the value of the duplexDistance leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_duplexDistance(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey and supportedChannelPlanKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_autoFreqSelectIsAvail
*
* Callback function for getting the value of the autoFreqSelectIsAvail leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_autoFreqSelectIsAvail(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey and supportedChannelPlanKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_channelBandwidth
*
* Callback function for getting the value of the channelBandwidth leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_channelBandwidth(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;
	val_value_t *transmissionModeIdKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);
	transmissionModeIdKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == transmissionModeIdKey, return NULL, "Could not find transmissionModeIdKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(transmissionModeIdKey), return NULL, "Could not access value of the key %s for element %s", transmissionModeIdKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey, supportedChannelPlanKey and transmissionModeIdKey as keys to find the information
	 */
	if (strcmp(VAL_STRING(layerProtocolKey), "LP-MWPS-TTP-ifIndex1") == 0)
	{
		if (strcmp(VAL_STRING(supportedChannelPlanKey), "ETSI") == 0)
		{
			if (strcmp(VAL_STRING(transmissionModeIdKey), "script_1") == 0)
			{
				return "28";
			}
			if (strcmp(VAL_STRING(transmissionModeIdKey), "script_2") == 0)
			{
				return "28";
			}
		}
		if (strcmp(VAL_STRING(supportedChannelPlanKey), "FCC") == 0)
		{
			if (strcmp(VAL_STRING(transmissionModeIdKey), "script_3") == 0)
			{
				return "56";
			}
			if (strcmp(VAL_STRING(transmissionModeIdKey), "script_4") == 0)
			{
				return "56";
			}
		}
	}
	if (strcmp(VAL_STRING(layerProtocolKey), "LP-MWPS-TTP-ifIndex2") == 0)
	{
		if (strcmp(VAL_STRING(supportedChannelPlanKey), "ETSI") == 0)
		{
			if (strcmp(VAL_STRING(transmissionModeIdKey), "script_1") == 0)
			{
				return "14";
			}
			if (strcmp(VAL_STRING(transmissionModeIdKey), "script_2") == 0)
			{
				return "14";
			}
		}
		if (strcmp(VAL_STRING(supportedChannelPlanKey), "FCC") == 0)
		{
			if (strcmp(VAL_STRING(transmissionModeIdKey), "script_3") == 0)
			{
				return "7";
			}
			if (strcmp(VAL_STRING(transmissionModeIdKey), "script_4") == 0)
			{
				return "7";
			}
		}
	}

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_modulationScheme
*
* Callback function for getting the value of the modulationScheme leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_modulationScheme(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;
	val_value_t *transmissionModeIdKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);
	transmissionModeIdKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == transmissionModeIdKey, return NULL, "Could not find transmissionModeIdKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(transmissionModeIdKey), return NULL, "Could not access value of the key %s for element %s", transmissionModeIdKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey, supportedChannelPlanKey and transmissionModeIdKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_informationRate
*
* Callback function for getting the value of the informationRate leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_informationRate(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;
	val_value_t *transmissionModeIdKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);
	transmissionModeIdKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == transmissionModeIdKey, return NULL, "Could not find transmissionModeIdKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(transmissionModeIdKey), return NULL, "Could not access value of the key %s for element %s", transmissionModeIdKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey, supportedChannelPlanKey and transmissionModeIdKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_txPowerMin
*
* Callback function for getting the value of the txPowerMin leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_txPowerMin(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;
	val_value_t *transmissionModeIdKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);
	transmissionModeIdKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == transmissionModeIdKey, return NULL, "Could not find transmissionModeIdKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(transmissionModeIdKey), return NULL, "Could not access value of the key %s for element %s", transmissionModeIdKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey, supportedChannelPlanKey and transmissionModeIdKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_txPowerMax
*
* Callback function for getting the value of the txPowerMax leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_txPowerMax(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;
	val_value_t *transmissionModeIdKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);
	transmissionModeIdKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == transmissionModeIdKey, return NULL, "Could not find transmissionModeIdKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(transmissionModeIdKey), return NULL, "Could not access value of the key %s for element %s", transmissionModeIdKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey, supportedChannelPlanKey and transmissionModeIdKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_rxThreshold
*
* Callback function for getting the value of the rxThreshold leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_rxThreshold(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;
	val_value_t *transmissionModeIdKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);
	transmissionModeIdKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == transmissionModeIdKey, return NULL, "Could not find transmissionModeIdKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(transmissionModeIdKey), return NULL, "Could not access value of the key %s for element %s", transmissionModeIdKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey, supportedChannelPlanKey and transmissionModeIdKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_amUpshiftLevel
*
* Callback function for getting the value of the amUpshiftLevel leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_amUpshiftLevel(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;
	val_value_t *transmissionModeIdKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);
	transmissionModeIdKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == transmissionModeIdKey, return NULL, "Could not find transmissionModeIdKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(transmissionModeIdKey), return NULL, "Could not access value of the key %s for element %s", transmissionModeIdKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey, supportedChannelPlanKey and transmissionModeIdKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_amDownshiftLevel
*
* Callback function for getting the value of the amDownshiftLevel leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_amDownshiftLevel(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;
	val_value_t *transmissionModeIdKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);
	transmissionModeIdKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == transmissionModeIdKey, return NULL, "Could not find transmissionModeIdKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(transmissionModeIdKey), return NULL, "Could not access value of the key %s for element %s", transmissionModeIdKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey, supportedChannelPlanKey and transmissionModeIdKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_xpicIsAvail
*
* Callback function for getting the value of the xpicIsAvail leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceCapability_supportedChannelPlanList_transmissionModeList_xpicIsAvail(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *supportedChannelPlanKey = NULL;
	val_value_t *transmissionModeIdKey = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	supportedChannelPlanKey = agt_get_key_value(parentHavingKey, &lastkey);
	transmissionModeIdKey = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == supportedChannelPlanKey, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == transmissionModeIdKey, return NULL, "Could not find transmissionModeIdKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(supportedChannelPlanKey), return NULL, "Could not access value of the key %s for element %s", supportedChannelPlanKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(transmissionModeIdKey), return NULL, "Could not access value of the key %s for element %s", transmissionModeIdKey->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey, supportedChannelPlanKey and transmissionModeIdKey as keys to find the information
	 */

	return NULL;
}

/********************************************************************
* FUNCTION cb_get_boot_time_airInterfaceConfiguration_problemKindSeverity
*
* Callback function for getting the value of the problemKindSeverity leaf
*
* INPUTS:
* val_value_t *element - the element for which we want the value
*
* RETURNS:
* The value of the element, represented as a string
********************************************************************/
static const char* cb_get_boot_time_airInterfaceConfiguration_problemKindSeverity(val_value_t *element)
{
	val_value_t *lastkey = NULL;
	val_value_t *layerProtocolKey = NULL;
	val_value_t *problemKindName = NULL;

	val_value_t* parentHavingKey = element->parent;

	YUMA_ASSERT(NULL == parentHavingKey, return NULL, "Could not find parent of element %s", element->name);
	layerProtocolKey = agt_get_key_value(parentHavingKey, &lastkey);
	problemKindName = agt_get_key_value(parentHavingKey, &lastkey);

	YUMA_ASSERT(NULL == layerProtocolKey, return NULL, "Could not find layerProtocolKey for element %s", element->name);
	YUMA_ASSERT(NULL == problemKindName, return NULL, "Could not find supportedChannelPlanKey for element %s", element->name);
	YUMA_ASSERT(NULL == VAL_STRING(layerProtocolKey), return NULL, "Could not access value of the key %s for element %s", layerProtocolKey->name, element->name);
	YUMA_ASSERT(NULL == VAL_STRING(problemKindName), return NULL, "Could not access value of the key %s for element %s", problemKindName->name, element->name);

	/*
	 * return the actual value for the attribute here, represented as a string, using the layerProtocolKey and problemKindName
	 */

	if (strcmp(VAL_STRING(problemKindName), "alarm1") == 0)
	{
		return "non-alarmed";
	}
	else if (strcmp(VAL_STRING(problemKindName), "alarm2") == 0)
	{
		return "warning";
	}
	else if (strcmp(VAL_STRING(problemKindName), "alarm3") == 0)
	{
		return "minor";
	}
	else if (strcmp(VAL_STRING(problemKindName), "alarm4") == 0)
	{
		return "major";
	}
	else if (strcmp(VAL_STRING(problemKindName), "alarm5") == 0)
	{
		return "critical";
	}

	return NULL;
}