FROM node:latest

WORKDIR /usr/src/app

RUN apt-get update -y && apt-get install -y git
RUN npm install -g npm@9 tar@6 create-react-app@5
RUN npx create-react-app . -template typescript
RUN npm i react-router-dom styled-reset styled-components @types/styled-components
RUN npm i browser-image-compression axios socket.io-client @types/socket.io-client

RUN rm -rf src public tsconfig.json

COPY ./tool/ .

COPY webpackDevServer.config.js node_modules/react-scripts/config

EXPOSE 3000

CMD ["npm", "run", "start"]
