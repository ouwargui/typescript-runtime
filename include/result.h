#ifndef RESULT_H
#define RESULT_H

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

#endif // RESULT_H
