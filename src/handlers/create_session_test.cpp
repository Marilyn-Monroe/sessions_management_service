#include "create_session.hpp"

#include "userver/utest/utest.hpp"

UTEST(GenerateSessionID, Basic) {
  using sessions_management_service::handlers::GenerateSessionID;
  EXPECT_NE(GenerateSessionID("71eaad334d41489eabe325acc20361b1"), "");

  constexpr unsigned kSessionIDMinLength = 32;
  EXPECT_GE(GenerateSessionID("71eaad334d41489eabe325acc20361b1").size(), kSessionIDMinLength);

  EXPECT_NE(GenerateSessionID("71eaad334d41489eabe325acc20361b1"),
            GenerateSessionID("71eaad334d41489eabe325acc20361b1"));
}
