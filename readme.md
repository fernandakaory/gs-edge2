# Ponto+ - Agendamento facilitado
<div align="center">
  <img src="https://github.com/fernandakaory/gs-edge2/assets/126582859/f5df60d0-94ee-4a6e-b8cb-9a3c695df211" width="300"  alt="logotipo">
</div>

## Integrantes
- Fernanda Kaory Saito – RM 551104
- Lana Giulia Auada Leite – RM 551143

## Saúde e tecnologia
A saúde é fundamental para o bem-estar e a qualidade de vida de cada indivíduo. Saúde não se limita apenas à ausência de doenças, mas engloba um estado de completo bem-estar físico, mental e social. Essa ainda é uma questão de constante desenvolvimento e aprimoração, tendo em vista que a tecnologia avança cada vez mais, a saúde, como algo primado, também avança em pró de uma melhoria que atinja a todos. 
Atualmente já podemos contar com diversos serviços oferecidos na internet, como consultas online, acompanhamento médico remoto, exames feitos da própria residência do paciente etc. Todavia, ainda existem questões a serem supridas e melhoradas. Existe uma alta demanda pelo serviço da área da saúde e, consequentemente, é preciso uma boa e grande estrutura para lidar com essa demanda. 


## Problema identificado
<p>Para esta Global Solution, precisamos implementar uma solução que una inovação e tecnologia para atuar em prevenção, automação ou precisão, com o intuito garantir uma realidade melhor para o âmbito da saúde.</p>
<p>Partindo desta óptica, temos os Objetivos de Desenvolvimento Sustentável (ODS), uma agenda mundial adotada pela ONU  composta por 17 objetivos e 169 metas a serem atingidos até 2030.Nestes, a meta 3, em específico, 
  assegurar uma vida saudável e promover o bem-estar para todos, em todas as idades.</p>
<p>Assim, nós observamos que Muitos usuários de plano de saúde ainda sentem dificuldade em utilizar as plataformas oferecidas pelos convênios e os serviços que essas oferecem, sendo um destes o agendamento e solicitação de exames.
  De acordo com uma pesquisa feita pela Associação Paulista de Medicina (APM), as consultas médicas e os exames foram os serviços mais usados e os que mais registraram problemas. Em 2018, as dificuldades nas consultas médicas passaram de 64% para 76%. No caso dos exames passaram de 40% para 72%. 
  Estes dados, são indicações que uma vida saúdavel, não é uma possibilitada acessível a todos, uma vez que o agendamento de exames é dificultado.</p>
  <div align="center">
    <img src="https://github.com/fernandakaory/gs-edge2/assets/126582859/eec9ec5c-75b5-43ca-a3bf-935ed9cd74f6" width="600"  alt="logotipo">
  </div>

## Solução
<p>Nossa proposta consiste em desenvolver um aplicativo que visa otimizar a experiência do usuário ao solicitar exames, promovendo uma comunicação eficiente entre o convênio/usuário e os diversos locais de exame,
  sejam eles conveniados ou clínicas particulares. Através da simplificação e aprimoramento desse processo de comunicação, buscamos aprimorar também o agendamento direto entre o usuário e o local de serviço, proporcionando
  maior praticidade.</p>

<p>Além disso, o nosso aplicativo será projetado para aprimorar todas as etapas envolvidas no contexto mencionado, incluindo a solicitação do pedido médico, acompanhamento médico e acesso aos resultados de exames. 
  Dessa forma, buscamos criar uma solução abrangente que não apenas simplifique a interação entre o usuário e os serviços de saúde, mas também aprimore todos os aspectos relacionados a esse processo, proporcionando uma 
  experiência mais eficiente e satisfatória para todos os envolvidos.</p>

## Solução e IOT
<p>Na nossa plataforma, estamos introduzindo uma  aba de resultados médicos, proporcionando aos usuários um acesso fácil e rápido às informações sobre sua saúde. Nessa seção, é possível consultar 
 detalhes importantes, inclusive em situações em que seja necessário monitorar o paciente de forma mais intensiva.</p>
<p>Para garantir um acompanhamento eficiente, implementamos a integração de sensores. Utilizando o sensor DHT22, conseguimos medir a temperatura do paciente com precisão, proporcionando dados 
valiosos em tempo real. Além disso, incorporamos um gerador de pulso para simular o acompanhamento dos batimentos cardíacos do paciente.</p>
<p>Ao acessar a aba de resultados, os profissionais de saúde e cuidadores têm a capacidade de verificar automaticamente a temperatura e o batimento cardíaco do paciente. Isso não apenas agiliza a obtenção de 
informações cruciais, mas também permite uma resposta rápida e eficaz caso seja necessária alguma intervenção.</p>
<p>Através da IoT, conseguimos integrar os sensores ao sistema de forma eficiente, garantindo a transmissão segura e precisa dos dados para a plataforma. Além disso, incorporamos um código que registra o horário UTC de
cada leitura dos sensores, proporcionando um registro temporal preciso das informações coletadas.
Dessa forma, nossa plataforma não apenas oferece uma maneira conveniente de acessar resultados médicos, mas também introduz uma camada avançada de automação e monitoramento contínuo, proporcionando uma abordagem proativa
e eficaz para o cuidado com a saúde.</p>

## Recursos necessários para implementação da solução
<h3>O Hardware deste projeto, é composto essencialmente por: </h3>
Uma placa ESP 32, que conta com dois núcleos de 32 bits, responsável por permitir a conexão ao wifi ou blutooth, garantindo, assim, a implementação da Internet das Coisas no nosso protótipo.

<div align="center">
  <img src="https://github.com/fernandakaory/sprint3-edge/assets/126582859/2530d075-fcab-4b35-ad58-5eed09751ef7" >
</div>

Um sensor DHT22, para a leitura de temperatura
<div align="center">
  <img src="https://github.com/fernandakaory/gs-edge2/assets/126582859/8347f8e0-c770-461c-9d66-2dbd3d1b3d95" width="300" >
</div>

Um gerador de pulso, para simular a captação de batimentos cardíacos
<div align="center">
  <img src="https://github.com/fernandakaory/gs-edge2/assets/126582859/342c793a-50d2-4f6f-942f-696151e4aacf" >
</div>

<h3>Back-end</h3>
Para o Back-end do projeto será utilizado o Fiware. Esta, é uma plataforma de código aberto que fornece uma infraestrutura padrão e aberta para o desenvolvimento de aplicações e serviços inteligentes baseados em IoT. Desta maneira, faremos uso desta ferramenta para que os dados coletado a partir dos sensores de temperatura e de batimento, armazenados e transportado até a aplicação de front-end utilizada, na qual serão exibidos para nossos clientes por meio de uma interface simples e amigável.
<div align="center">
  <img src="https://github.com/fernandakaory/sprint3-edge/assets/126582859/dcd4980b-f53f-444d-99d6-4925a6668d87" >
</div>
<h3>Front-end</h3>
A base front-end que está sendo utilizada neste projeto na fase atual, é, basicamente, o <a href=https://freeboard.io/> freeboard </a>, uma plataforma que nos oferece todos os recursos necessários para a exibição dos dados de lotação que são enviados por MQTT, a partir do Fiware Orion. Assim é possível vizualizar os dados captados pelos sensores de maneira simples e intuitiva. Escolhemos o freeboard com o intuíto de ser simples e de fácil utilização, para garantir  acessibilidade e uma boa experiência.

<div align="center">
  <img src="https://github.com/fernandakaory/gs-edge2/assets/126582859/2198455c-be5d-4d0b-8d7f-f610aeefe1d8" width="600" >

</div>


## Requisitos do projeto
- Docker e docker compose
- Fiware
- Postman
- Em caso de construção física, uma ESP 32 , sensor DHT22, display lcd I2C e um gerador de pulso
- Em caso de prototipação virtual, as ferramentas podem ser encontradas e usadas no <a href="https://wokwi.com/"> Wokwi </a>
- Conectividade Wifi ou blutooth
- Ambiente front-end, como o <a href=https://freeboard.io/> freeboard </a>
  
## Configuração e reprodução
1. Instalação de uma máquina virtual Linux
2. Instalação do docker e do docker compose como especificado <a href=https://docs.docker.com/engine/install/ubuntu/> aqui </a>.
3. Instalação do <a href=https://github.com/fabiocabrini/fiware> Fiware</a>.
4. Instalação do Postman
5. Importar as collection para o Fiware e executar os métodos HTTP de Health Check
6. Provisionar os sensores como dispositivos virtuais (como no arquivo json acima), definindo id, protocolo de comunicação, comandos e atributos.
7. Registrar esses dispositivos  (como no arquivo json acima).
8. Montar os sensores físicos na ESP 32.
9. Montar o código desses sensores para enviar por MQTT os dados.
10. Realizar a subscrição e métodos GET para receber os dados desejados.
11. Configurar <a href=https://freeboard.io/> freeboard </a>
12. Configurar os dashboards e gráficos desejados
