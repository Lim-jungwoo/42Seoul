FROM node:latest
WORKDIR /app

RUN npm install -g npm@9
COPY . .
RUN npm install

RUN npm run build
EXPOSE 4000
CMD ["npm", "run", "start:migrate:prod"]
