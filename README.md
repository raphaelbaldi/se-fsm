Este repositório contém as soluções para os problemas descritos abaixo. (2018/2)

# Sistemas Embarcados - Trabalho - Aula 13
O objetivo do trabalho é modelar os problemas utilizando um subconjunto de linguagem.

Em duplas ou trios, entregar o código comentado dos 3 problemas propostos em um arquivo compactado.

Você poderá implementar um problema diferente se assim desejar (escolha um dos casos para ser substituído) bastando fornecer juntamente com o seu código uma descrição do problema.

O trabalho deverá ser entregue pelo Moodle. Apenas um integrante deve submeter o trabalho.

Além do enunciado está sendo disponibilizado um exemplo em C (controle de elevador simplificado - [fsm.c](sample/fsm.c)). Você pode utilizar qualquer linguagem de programação para esse trabalho.

## 1 - Portas duplas de bancos ([`double_door.c`](double_door.c))
Com o uso de um subconjunto da linguagem, modele com uma FSM uma solução para o controle de uma porta de banco (porta dupla).

## 2 - Travas automáticas de carros ([`car_lock.c`](car_lock.c))
Utilizando a abordagem de subconjunto da linguagem, modele uma FSM para solucionar o problema de controle das travas das portas de um carro. O controle precisa considerar a velocidade do veículo (> 30km/h), botão de trava das portas traseiras e acionamento das portas para abertura.

## 3 - Assento ejetor de jato supersônico ([`ejection_seat.c`](ejection_seat.c))
Modele utilizando HCFSM o controle para o acionamento de ejeção do assento do piloto de um jato militar. Considere o que pode acontecer se o piloto acionar o sistema com o avião em posição desfavorável (cabeça para baixo ou ângulo errado) ou velocidade supersônica (> 1225km/h). O controle precisa de duas confirmações de ejeção em menos de 1 segundo para ser ativado.
