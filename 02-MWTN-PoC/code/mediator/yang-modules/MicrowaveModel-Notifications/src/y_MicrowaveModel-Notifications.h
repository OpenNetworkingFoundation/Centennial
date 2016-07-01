
#ifndef _H_y_MicrowaveModel_Notifications
#define _H_y_MicrowaveModel_Notifications
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
    module MicrowaveModel-Notifications
    revision 2016-03-20
    namespace uri:onf:MicrowaveModel-Notifications

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

#define y_MicrowaveModel_Notifications_M_MicrowaveModel_Notifications (const xmlChar *)"MicrowaveModel-Notifications"
#define y_MicrowaveModel_Notifications_R_MicrowaveModel_Notifications (const xmlChar *)"2016-03-20"

#define y_MicrowaveModel_Notifications_N_AttributeValueChangedNotification (const xmlChar *)"AttributeValueChangedNotification"
#define y_MicrowaveModel_Notifications_N_ObjectCreationNotification (const xmlChar *)"ObjectCreationNotification"
#define y_MicrowaveModel_Notifications_N_ObjectDeletionNotification (const xmlChar *)"ObjectDeletionNotification"
#define y_MicrowaveModel_Notifications_N_ProblemNotification (const xmlChar *)"ProblemNotification"
#define y_MicrowaveModel_Notifications_N_attributeName (const xmlChar *)"attributeName"
#define y_MicrowaveModel_Notifications_N_counter (const xmlChar *)"counter"
#define y_MicrowaveModel_Notifications_N_newValue (const xmlChar *)"newValue"
#define y_MicrowaveModel_Notifications_N_objectID (const xmlChar *)"objectID"
#define y_MicrowaveModel_Notifications_N_objectId (const xmlChar *)"objectId"
#define y_MicrowaveModel_Notifications_N_problem (const xmlChar *)"problem"
#define y_MicrowaveModel_Notifications_N_severity (const xmlChar *)"severity"
#define y_MicrowaveModel_Notifications_N_timeStamp (const xmlChar *)"timeStamp"
/********************************************************************
* FUNCTION y_MicrowaveModel_Notifications_init
* 
* initialize the MicrowaveModel-Notifications server instrumentation library
* 
* INPUTS:
*    modname == requested module name
*    revision == requested version (NULL for any)
* 
* RETURNS:
*     error status
********************************************************************/
extern status_t y_MicrowaveModel_Notifications_init (
    const xmlChar *modname,
    const xmlChar *revision);

/********************************************************************
* FUNCTION y_MicrowaveModel_Notifications_init2
* 
* SIL init phase 2: non-config data structures
* Called after running config is loaded
* 
* RETURNS:
*     error status
********************************************************************/
extern status_t y_MicrowaveModel_Notifications_init2 (void);

/********************************************************************
* FUNCTION y_MicrowaveModel_Notifications_cleanup
*    cleanup the server instrumentation library
* 
********************************************************************/
extern void y_MicrowaveModel_Notifications_cleanup (void);

#ifdef __cplusplus
} /* end extern 'C' */
#endif

#endif