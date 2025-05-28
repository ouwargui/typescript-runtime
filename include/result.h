#define DECL_RESULT(name, OK, ERR) \
  typedef struct                   \
  {                                \
    enum                           \
    {                              \
      name##_OK,                   \
      name##_ERR                   \
    } type;                        \
    union                          \
    {                              \
      OK ok;                       \
      ERR err;                     \
    };                             \
  } name##_result_t;
