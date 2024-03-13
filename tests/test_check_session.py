import handlers.sessions_management_pb2 as sessions_management_protos


# Start via `make test-debug` or `make test-release`
async def test_check_exists_session(grpc_service):
    request = sessions_management_protos.CheckSessionRequest(
        session_id='018e389119297ad8a3b97a866d880d59')
    response = await grpc_service.CheckSession(request)
    assert response.status


async def test_check_non_exists_session(grpc_service):
    request = sessions_management_protos.CheckSessionRequest(
        session_id='018e389641ca765aa9723320d1a9df6c')
    response = await grpc_service.CheckSession(request)
    assert not response.status
