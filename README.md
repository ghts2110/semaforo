[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/6JttSM6H)
# Apresentação da Atividade
<img src="assets/images/Unicap_Icam_Tech-01.png" alt="drawing" width="250"/>

## Identificação
**Disciplina**: Sistemas Operacionais
\
**Atividade**: Implementando Mutex

## Instruções
- *Commits* fora do prazo **serão completamente desconsiderados**

##  Descrição

Implemente em `C` um simulador de cruzamento viário formado por **quatro ruas**. Cada via deve ser equipada com um semáforo de trânsito, controlando o fluxo de veículos que tentam atravessar enquanto seguem as regras de trânsito. 

As seguintes funcionalidades devem ser implementadas:

- Os semáforos devem alternar entre os estados de sinalização (verde, amarelo e vermelho) de acordo com o mundo real
- Os carros devem ser implementados com `threads`. Caso queira, pode usar `thread`para outra funcionalidade
- A densidade do tráfego deve ser decidido de forma aleatória, porém, no mínimo, cada simulação deve conter 2 carros em ruas diferentes
- O simulador deve garantir que apenas uma direção tenha o sinal verde em um determinado momento, evitando colisão entre os veículos
- O simulador deve incluir algum tipo de visualização do seu funcionamento, de forma clara e compreensível. Uma opção é exibir no terminal, igual ao demonstrado no arquivo `exemplo.c`
- Na visualização, é obrigatório que cada carro seja identificado de forma única. Por exemplo, nomes como C1, C2, etc.
- **O número de ruas é fixado em 4**
- **O uso de mutex é o obrigatório**. Outros mecanismo de sincronização não são permitidos

## Sobre a entrega
- Todo o código deve ser documentado, fornecendo informações sobre a implementação de cada tarefa. O documento deve ser entregue em um arquivo PDF explicando detalhadamente as decisões definidas pelo grupo
- Código-fonte em `C`

## Sobre a correção

- O simulador deve funcionar corretamente, alternando entre as cores do semáforo de trânsito e permitindo o fluxo de veículos
- Uso adequado de `thread` e `mutex`
- Todo o sistema aleatório, sem qualquer interação com o usuário
- Visualização de acordo com a sincronização de `threads`
- A nota é individual e cada membro será avaliado de acordo com sua participação registrada no GitHub. Mudanças simples, como alteração de nome de uma váriavel, não serão consideradas. Cada contribuição deve ser efetiva para o desenvolvimento do simulador. O número de `commits`, por exemplo, é um indicador relevante. 
