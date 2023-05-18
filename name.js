const fs = require('fs');

// Função para ler o arquivo e fazer o filtro
function filtrarNomeEMatricula(nomeArquivo) {
  const dados = fs.readFileSync(nomeArquivo, 'utf8');
  const linhas = dados.split('\n');
  const alunos = [];

  linhas.forEach(linha => {
    const partes = linha.trim().split(' ');
    const matricula = partes[0];
    const primeiroNome = partes[1];
    alunos.push({ matricula, primeiroNome });
  });

  return alunos;
}

// Função para escrever a matrícula e o nome dos alunos em um arquivo txt
function escreverAlunosEmArquivo(alunos, nomeArquivo) {
  let dados = '';

  alunos.forEach(aluno => {
    const linha = `${aluno.matricula} ${aluno.primeiroNome}\n`;
    dados += linha;
  });

  fs.writeFileSync(nomeArquivo, dados);
}

// Exemplo de uso
const arquivo = 'ufg.txt';
const alunosFiltrados = filtrarNomeEMatricula(arquivo);
console.log(alunosFiltrados);

const arquivoSaida = 'ufg2.txt';
escreverAlunosEmArquivo(alunosFiltrados, arquivoSaida);