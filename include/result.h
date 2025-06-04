#ifndef RESULT_H
#define RESULT_H

#define DECL_RESULT(name, OK, ERR) \
  struct name##_result             \
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
  };

#endif // RESULT_H
