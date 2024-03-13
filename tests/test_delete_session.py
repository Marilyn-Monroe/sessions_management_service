import handlers.sessions_management_pb2 as sessions_management_protos


# Start via `make test-debug` or `make test-release`
async def test_delete_exists_session(grpc_service):
    request = sessions_management_protos.DeleteSessionRequest(
        session_id='018e389119297ad8a3b97a866d880d59')
    response = await grpc_service.DeleteSession(request)
    assert response.status


async def test_delete_non_exists_session(grpc_service):
    request = sessions_management_protos.DeleteSessionRequest(
        session_id='018e389119297ad8a3b97a866d880d59')
    response = await grpc_service.DeleteSession(request)
    assert not response.status
