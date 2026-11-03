console.log("Script da loja Passo Leve carregado!");

const fotoPrincipal = document.getElementById("foto-principal");

const btnAzul = document.getElementById("btn-azul");
const btnVerde = document.getElementById("btn-verde");
const btnCoral = document.getElementById("btn-coral");

const corEscolhida = document.getElementById("cor-escolhida");

const btnDetalhes = document.getElementById("btn-detalhes");
const detalhes = document.getElementById("detalhes");

const btnFavorito = document.getElementById("btn-favorito");
const btnCarrinho = document.getElementById("btn-carrinho");

const tam38 = document.getElementById("tam-38");
const tam40 = document.getElementById("tam-40");
const tam42 = document.getElementById("tam-42");
const tamanhoEscolhido = document.getElementById("tamanho-escolhido");

const miniAzul = document.getElementById("mini-azul");
const miniVerde = document.getElementById("mini-verde");
const miniCoral = document.getElementById("mini-coral");

function selecionarAzul() {
  fotoPrincipal.setAttribute("src", "img/tenis-azul.svg");
  corEscolhida.textContent = "Cor escolhida: Azul";
}

function selecionarVerde() {
  fotoPrincipal.setAttribute("src", "img/tenis-verde.svg");
  corEscolhida.textContent = "Cor escolhida: Verde";
}

function selecionarCoral() {
  fotoPrincipal.setAttribute("src", "img/tenis-coral.svg");
  corEscolhida.textContent = "Cor escolhida: Coral";
}

btnAzul.addEventListener("click", selecionarAzul);
btnVerde.addEventListener("click", selecionarVerde);
btnCoral.addEventListener("click", selecionarCoral);

function mostrarDetalhes() {
  detalhes.innerHTML = `
    <ul>
      <li>Cabedal leve e respirável.</li>
      <li>Solado emborrachado para melhor aderência.</li>
      <li>Entressola macia para maior conforto.</li>
      <li>Indicado para caminhadas e uso no dia a dia.</li>
    </ul>
  `;
}

btnDetalhes.addEventListener("click", mostrarDetalhes);

btnFavorito.addEventListener("click", function () {
  btnFavorito.classList.toggle("favorito");

  if (btnFavorito.classList.contains("favorito")) {
    btnFavorito.textContent = "♥ Favoritado";
  } else {
    btnFavorito.textContent = "♥ Favoritar";
  }
});

btnCarrinho.addEventListener("click", function () {
  btnCarrinho.textContent = "Adicionado ao carrinho!";
  btnCarrinho.style.backgroundColor = "#3E8E6A";
});

function destacarFoto() {
  fotoPrincipal.classList.add("destaque");
}

function removerDestaqueFoto() {
  fotoPrincipal.classList.remove("destaque");
}

fotoPrincipal.addEventListener("mouseover", destacarFoto);
fotoPrincipal.addEventListener("mouseout", removerDestaqueFoto);

function selecionarTamanho(tamanho) {
  tamanhoEscolhido.textContent = `Tamanho escolhido: ${tamanho}`;

  [tam38, tam40, tam42].forEach(function (botao) {
    botao.style.backgroundColor = "#FFFFFF";
    botao.style.color = "#1F2933";
  });

  const botaoSelecionado = document.getElementById(`tam-${tamanho}`);
  botaoSelecionado.style.backgroundColor = "#1F2933";
  botaoSelecionado.style.color = "#FFFFFF";
}

tam38.addEventListener("click", function () {
  selecionarTamanho("38");
});

tam40.addEventListener("click", function () {
  selecionarTamanho("40");
});

tam42.addEventListener("click", function () {
  selecionarTamanho("42");
});

const btnTema = document.querySelector("#btn-tema");

btnTema.addEventListener("click", function () {
  document.body.classList.toggle("escuro");

  if (document.body.classList.contains("escuro")) {
    btnTema.textContent = "Modo claro";
  } else {
    btnTema.textContent = "Modo escuro";
  }
});

miniAzul.addEventListener("mouseover", selecionarAzul);
miniVerde.addEventListener("mouseover", selecionarVerde);
miniCoral.addEventListener("mouseover", selecionarCoral);
