# Aplicativo de serviços BLE

- Componentes do aplicativo:
    - Menu de notificações: exibe informações solicitadas pelo usuário ou notificadas pelo dispositivo conectado
    - Menu de status de conexão: exibe o status de conexão do aplicativo e permite desconectar do dispositivo quando conectado
    - Menu de opções BLE: 
        - Ler valor da característica
        - Escrever na característica
        - Recuperar valor no índice x

## Nenhum dispositivo conectado

- Ao iniciar, o aplicativo busca por dispostivos disponíveis durante 5 segundos
- Botão de busca de dispositivos: o aplicativo busca por dispostivos disponíveis durante 5 segundos

## Dispositivo conectado

- Ao selecionar um dispositivo as seguintes opções se tornam disponíveis:
    - Desconectar dispositivo
    - Ler valor da característica
    - Escrever na característica
    - Recuperar valor no índice x
- Selecionando a opção de ler o conteúdo da característica, o valor será exibido na barra de notificações
- Selecionando a opção de escrever na característica, será exibido um menu descrita, onde o usuário poderá escrever um valor e enviar para o dispositivo
- As operaçoes acima serão realizadas sobre o índice selecionado