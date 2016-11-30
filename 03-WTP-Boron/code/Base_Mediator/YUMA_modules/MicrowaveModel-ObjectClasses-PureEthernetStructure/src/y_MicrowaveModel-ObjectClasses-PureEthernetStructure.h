
#ifndef _H_y_MicrowaveModel_ObjectClasses_PureEthernetStructure
#define _H_y_MicrowaveModel_ObjectClasses_PureEthernetStructure
/* 
 * Copyright (c) 2008-2012, Andy Bierman, All Rights Reserved.
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *

*** Generated by yangdump 2.5-5

    Yuma SIL header
    module MicrowaveModel-ObjectClasses-PureEthernetStructure
    revision 2016-09-02
    namespace uri:onf:MicrowaveModel-ObjectClasses-PureEthernetStructure
    organization ONF (Open Networking Foundation) Open Transport Working Group - Wireless Transport Project

 */

#include <xmlstring.h>

#include "dlq.h"
#include "ncxtypes.h"
#include "op.h"
#include "status.h"
#include "val.h"

#ifdef __cplusplus
extern "C" {
#endif

#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_M_MicrowaveModel_ObjectClasses_PureEthernetStructure (const xmlChar *)"MicrowaveModel-ObjectClasses-PureEthernetStructure"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_R_MicrowaveModel_ObjectClasses_PureEthernetStructure (const xmlChar *)"2016-09-02"

#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_MW_PureEthernetStructure_Pac (const xmlChar *)"MW_PureEthernetStructure_Pac"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_administrativeState (const xmlChar *)"administrativeState"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_currentPerformanceDataList (const xmlChar *)"currentPerformanceDataList"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_currentProblemList (const xmlChar *)"currentProblemList"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_elapsedTime (const xmlChar *)"elapsedTime"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_granularityPeriod (const xmlChar *)"granularityPeriod"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_historicalPerformanceDataList (const xmlChar *)"historicalPerformanceDataList"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_historyDataId (const xmlChar *)"historyDataId"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_lastStatusChange (const xmlChar *)"lastStatusChange"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_layerProtocol (const xmlChar *)"layerProtocol"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_nameBinding (const xmlChar *)"nameBinding"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_objectClass (const xmlChar *)"objectClass"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_operationalStatus (const xmlChar *)"operationalStatus"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_performanceData (const xmlChar *)"performanceData"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_periodEndTime (const xmlChar *)"periodEndTime"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_problemKindName (const xmlChar *)"problemKindName"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_problemKindSeverity (const xmlChar *)"problemKindSeverity"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_problemKindSeverityList (const xmlChar *)"problemKindSeverityList"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_problemName (const xmlChar *)"problemName"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_problemSeverity (const xmlChar *)"problemSeverity"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_pureEthernetStructureCapability (const xmlChar *)"pureEthernetStructureCapability"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_pureEthernetStructureConfiguration (const xmlChar *)"pureEthernetStructureConfiguration"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_pureEthernetStructureCurrentPerformance (const xmlChar *)"pureEthernetStructureCurrentPerformance"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_pureEthernetStructureCurrentProblems (const xmlChar *)"pureEthernetStructureCurrentProblems"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_pureEthernetStructureHistoricalPerformances (const xmlChar *)"pureEthernetStructureHistoricalPerformances"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_pureEthernetStructureStatus (const xmlChar *)"pureEthernetStructureStatus"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_scannerId (const xmlChar *)"scannerId"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_segmentIsReservedForTdm (const xmlChar *)"segmentIsReservedForTdm"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_segmentStatusList (const xmlChar *)"segmentStatusList"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_segmentStatusTypeId (const xmlChar *)"segmentStatusTypeId"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_sequenceNumber (const xmlChar *)"sequenceNumber"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_structureId (const xmlChar *)"structureId"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_supportedAlarms (const xmlChar *)"supportedAlarms"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_suspectIntervalFlag (const xmlChar *)"suspectIntervalFlag"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_timeStamp (const xmlChar *)"timeStamp"
#define y_MicrowaveModel_ObjectClasses_PureEthernetStructure_N_timestamp (const xmlChar *)"timestamp"
/********************************************************************
* FUNCTION y_MicrowaveModel_ObjectClasses_PureEthernetStructure_init
* 
* initialize the MicrowaveModel-ObjectClasses-PureEthernetStructure server instrumentation library
* 
* INPUTS:
*    modname == requested module name
*    revision == requested version (NULL for any)
* 
* RETURNS:
*     error status
********************************************************************/
extern status_t y_MicrowaveModel_ObjectClasses_PureEthernetStructure_init (
    const xmlChar *modname,
    const xmlChar *revision);

/********************************************************************
* FUNCTION y_MicrowaveModel_ObjectClasses_PureEthernetStructure_init2
* 
* SIL init phase 2: non-config data structures
* Called after running config is loaded
* 
* RETURNS:
*     error status
********************************************************************/
extern status_t y_MicrowaveModel_ObjectClasses_PureEthernetStructure_init2 (void);

/********************************************************************
* FUNCTION y_MicrowaveModel_ObjectClasses_PureEthernetStructure_cleanup
*    cleanup the server instrumentation library
* 
********************************************************************/
extern void y_MicrowaveModel_ObjectClasses_PureEthernetStructure_cleanup (void);

status_t MicrowaveModel_ObjectClasses_PureEthernetStructure_MW_PureEthernetStructure_Pac_pureEthernetStructureStatus_mro (val_value_t *parentval);

status_t MicrowaveModel_ObjectClasses_PureEthernetStructure_MW_PureEthernetStructure_Pac_pureEthernetStructureCurrentProblems_currentProblemList_timeStamp_get (ses_cb_t *scb, getcb_mode_t cbmode, const val_value_t *virval, val_value_t *dstval);
status_t MicrowaveModel_ObjectClasses_PureEthernetStructure_MW_PureEthernetStructure_Pac_pureEthernetStructureCurrentProblems_currentProblemList_problemName_get (ses_cb_t *scb, getcb_mode_t cbmode, const val_value_t *virval, val_value_t *dstval);
status_t MicrowaveModel_ObjectClasses_PureEthernetStructure_MW_PureEthernetStructure_Pac_pureEthernetStructureCurrentProblems_currentProblemList_problemSeverity_get (ses_cb_t *scb, getcb_mode_t cbmode, const val_value_t *virval, val_value_t *dstval);




#ifdef __cplusplus
} /* end extern 'C' */
#endif

#endif