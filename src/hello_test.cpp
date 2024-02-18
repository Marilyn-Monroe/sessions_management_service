#include "hello.hpp"

#include <userver/utest/utest.hpp>

UTEST(SayHelloTo, Basic) {
  EXPECT_EQ(sessions_management_service::SayHelloTo("Developer"), "Hello, Developer!\n");
  EXPECT_EQ(sessions_management_service::SayHelloTo({}), "Hello, unknown user!\n");
}
