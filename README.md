Este repositório contém as soluções para os problemas descritos abaixo. (2018/2)

# Sistemas Embarcados - Trabalho - Aula 13
## 1 - Portas duplas de bancos ([`double_door.c`](double_door.c))
Com o uso de um subconjunto da linguagem, modele com uma FSM uma solução para o controle de uma porta de banco (porta dupla).

## 2 - Travas automáticas de carros ([`car_lock.c`](car_lock.c))
Utilizando a abordagem de subconjunto da linguagem, modele uma FSM para solucionar o problema de controle das travas das portas de um carro. O controle precisa considerar a velocidade do veículo (> 30km/h), botão de trava das portas traseiras e acionamento das portas para abertura.

## 3 - Assento ejetor de jato supersônico ([`ejection_seat.c`](ejection_seat.c))
Modele utilizando HCFSM o controle para o acionamento de ejeção do assento do piloto de um jato militar. Considere o que pode acontecer se o piloto acionar o sistema com o avião em posição desfavorável (cabeça para baixo ou ângulo errado) ou velocidade supersônica (> 1225km/h). O controle precisa de duas confirmações de ejeção em menos de 1 segundo para ser ativado.
