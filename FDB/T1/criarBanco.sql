DROP DATABASE CopaDoMundo;
CREATE DATABASE CopaDoMundo;

USE CopaDoMundo;

CREATE TABLE Paises (
    idPais INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(255) NOT NULL UNIQUE
);

CREATE TABLE Edicoes (
    idEdicao INT PRIMARY KEY AUTO_INCREMENT,
    ano INT NOT NULL UNIQUE
);

CREATE TABLE Partidas (
    idPartida INT PRIMARY KEY AUTO_INCREMENT,
    idEdicao INT NOT NULL,
    fase VARCHAR(50) NOT NULL,
    idTimeCasa INT,
    idTimeFora INT,
    golsTimeCasa INT,
    golsTimeFora INT,
    observacoesPlacar VARCHAR(50),
    FOREIGN KEY (idEdicao) REFERENCES Edicoes(idEdicao),
    FOREIGN KEY (idTimeCasa) REFERENCES Paises(idPais),
    FOREIGN KEY (idTimeFora) REFERENCES Paises(idPais)
);

CREATE TABLE EdicaoSedes (
    idEdicao INT,
    idPais INT,
    PRIMARY KEY (idEdicao, idPais),
    FOREIGN KEY (idEdicao) REFERENCES Edicoes(idEdicao),
    FOREIGN KEY (idPais) REFERENCES Paises(idPais)
);

CREATE TABLE Jogador (
    idJogador INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(255) NOT NULL,
    idPais INT,
    totalGols INT NOT NULL DEFAULT 0,
    totalPartidas INT NOT NULL DEFAULT 0,
    FOREIGN KEY (idPais) REFERENCES Paises(idPais)
);

CREATE TABLE ParticipacaoJogador (
    idEdicao INT,
    idJogador INT,
    PRIMARY KEY (idEdicao, idJogador),
    FOREIGN KEY (idEdicao) REFERENCES Edicoes(idEdicao),
    FOREIGN KEY (idJogador) REFERENCES Jogador(idJogador)
);