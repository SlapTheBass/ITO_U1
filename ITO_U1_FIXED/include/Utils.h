#pragma once

typedef enum E_action { eNORTH, eSOUTH, eEAST, eWEST };

typedef enum E_tileType { eEMPTY, eAGENT, eOBSTACLE, eEXIT, eVOID };

typedef enum E_tileStatus { eINACTIVE, eACTIVE };

typedef enum E_appState { eONINIT, eSTART, eCLOSE };

typedef enum E_keys { eNONE, eINC_SIZE, eDEC_SIZE, eRESET, eSPACE, eQUIT };

enum class  E_objectType { eNONE, eOBSTACLE, eEXIT };