DROP DATABASE CopaDoMundo;
CREATE DATABASE CopaDoMundo;

USE CopaDoMundo;

CREATE TABLE Paises (
    idPais INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(255) NOT NULL UNIQUE
);

CREATE TABLE Edicoes (
    idEdicao INT PRIMARY KEY AUTO_INCREMENT,
    ano INT NOT NULL UNIQUE,
    idCampeao INT,
    idViceCampeao INT,
    idTerceiro INT,
    idQuarto INT,
    FOREIGN KEY (idCampeao) REFERENCES Paises(idPais),
    FOREIGN KEY (idViceCampeao) REFERENCES Paises(idPais),
    FOREIGN KEY (idTerceiro) REFERENCES Paises(idPais),
    FOREIGN KEY (idQuarto) REFERENCES Paises(idPais)
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