typedef enum
{
  t_con,
  t_id,
  t_opr
} node_enum_t;

typedef struct
{
  node_enum_t type;
  int value;
} node_con_t;

typedef struct
{
  node_enum_t type;
  int i;
} node_id_t;

typedef struct
{
  node_enum_t type;
  int oper;
  int nops;
  union node_type_tag *op[1];
} node_opr_t;

typedef union node_type_tag
{
  node_enum_t type;
  node_con_t con;
  node_id_t id;
  node_opr_t opr;
} node_t;
