import handlers.sessions_management_pb2 as sessions_management_protos


# Start via `make test-debug` or `make test-release`
async def test_create_session(grpc_service):
    request = sessions_management_protos.CreateSessionRequest(
        user_id='71eaad334d41489eabe325acc20361b1')
    response = await grpc_service.CreateSession(request)
    assert response.session_id != ''
    assert len(response.session_id) >= 32


async def test_create_session_exists_user(grpc_service):
    request = sessions_management_protos.CreateSessionRequest(
        user_id='71eaad334d41489eabe325acc20361b1')
    response = await grpc_service.CreateSession(request)
    assert response.session_id != ''
    assert len(response.session_id) >= 32
