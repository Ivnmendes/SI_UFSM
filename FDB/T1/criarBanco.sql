DROP DATABASE CopaDoMundo;
CREATE DATABASE CopaDoMundo;

USE CopaDoMundo;

CREATE TABLE Pais (
    idPais INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(255) NOT NULL UNIQUE
);

CREATE TABLE Edicao (
    idEdicao INT PRIMARY KEY AUTO_INCREMENT,
    ano INT NOT NULL UNIQUE
);

CREATE TABLE Partida (
    idPartida INT PRIMARY KEY AUTO_INCREMENT,
    idEdicao INT NOT NULL,
    fase VARCHAR(50) NOT NULL,
    idGanhador INT,
    idPerdedor INT,
    golsGanhador INT,
    golsPerdedor INT,
    observacoesPlacar VARCHAR(50),
    FOREIGN KEY (idEdicao) REFERENCES Edicao(idEdicao),
    FOREIGN KEY (idGanhador) REFERENCES Pais(idPais),
    FOREIGN KEY (idPerdedor) REFERENCES Pais(idPais)
);

CREATE TABLE EdicaoSede (
    idEdicao INT,
    idPais INT NOT NULL,
    PRIMARY KEY (idEdicao, idPais),
    FOREIGN KEY (idEdicao) REFERENCES Edicao(idEdicao),
    FOREIGN KEY (idPais) REFERENCES Pais(idPais)
);

CREATE TABLE Jogador (
    idJogador INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(255) NOT NULL,
    idPais INT,
    totalGols INT NOT NULL DEFAULT 0,
    totalPartidas INT NOT NULL DEFAULT 0,
    FOREIGN KEY (idPais) REFERENCES Pais(idPais)
);

CREATE TABLE ParticipacaoJogador (
    idEdicao INT NOT NULL,
    idJogador INT NOT NULL,
    PRIMARY KEY (idEdicao, idJogador),
    FOREIGN KEY (idEdicao) REFERENCES Edicao(idEdicao),
    FOREIGN KEY (idJogador) REFERENCES Jogador(idJogador)
);