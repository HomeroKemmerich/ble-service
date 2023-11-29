# ble-service

Repositório para desenvolvimento do trabalho sobre BLE. 

## Sumário

- [Aluno](#aluno)
- [Descrição](#descrição)
- [Recursos](#recursos)
- [Observações](#observações)

## Aluno 

- [Homero Kemmerich](146676@upf.br)

## Descrição

Criar um serviço BLE que execute numa ESP32, fornecendo característcas que suportam leitura, escrita e notificação. Criar ainda um aplicação para dispostivos móveis que realize uma interação com o serviço. 

O serviço deve ter sua documentação criada e anexada. Ele deve suportar (pelo menos):

- Leitura de uma característica;
- Escrita em característica;
- Recuperação de valor indexado (deve-se passar o índice);
- Notificar quando novos dados estão prontos:
- recuperação dos dados por característica;
- recuperação dos dados pela operação de notify;

O aplicativo para dispositivos móveis deve acessar as funcionalidades do serviço.

## Recursos

- Aplicativo móvel
    - [Documentação](./doc/app.md)
    - [Projeto](/files/ble_services.aia)
    - [.apk](./files/ble_services.apk)
- Firmware
    - [Documentação](/files/documentacao_ble-services.pdf)

## Observações

Apesar de implementado via firmware, e também via aplicativo, não foi possível implementar a leitura no índice nem de notificação por razões desconhecidas.