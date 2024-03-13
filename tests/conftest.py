import pathlib
import sys

import pytest
import json

import handlers.sessions_management_pb2_grpc as sessions_management_services

USERVER_CONFIG_HOOKS = ['prepare_service_config']

pytest_plugins = [
    'pytest_userver.plugins.grpc', 'pytest_userver.plugins.redis'
]


@pytest.fixture
def grpc_service(grpc_channel):
    return sessions_management_services.SessionsManagementServiceStub(
        grpc_channel)


@pytest.fixture(scope='session')
def mock_grpc_sessions_management_session(grpc_mockserver, create_grpc_mock):
    mock = create_grpc_mock(
        sessions_management_services.SessionsManagementServiceServicer)
    (sessions_management_services
        .add_SessionsManagementServiceServicer_to_server(
            mock.servicer, grpc_mockserver, ))
    return mock


@pytest.fixture
def mock_grpc_server(mock_grpc_sessions_management_session):
    with mock_grpc_sessions_management_session.mock() as mock:
        yield mock


@pytest.fixture(scope='session')
def prepare_service_config(grpc_mockserver_endpoint):
    def patch_config(config, config_vars):
        components = config['components_manager']['components']
        components['sessions-management-client'][
            'endpoint'] = grpc_mockserver_endpoint

    return patch_config


def pytest_configure():
    sys.path.append(
        str(pathlib.Path(__file__).parent.parent / 'proto/handlers/'))


@pytest.fixture(scope='session')
def service_env(redis_sentinels):
    secdist_config = {
        'redis_settings': {
            'redis_db_1': {
                'password': '',
                'sentinels': redis_sentinels,
                'shards': [{
                    'name': 'test_master0'
                }],
            },
        },
    }

    return {'SECDIST_CONFIG': json.dumps(secdist_config)}


@pytest.fixture(scope='session')
def redis_store(_redis_store):
    _redis_store.set('018e389119297ad8a3b97a866d880d59',
                     '71eaad334d41489eabe325acc20361b1')
