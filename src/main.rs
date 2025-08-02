use std::{io::{BufRead, Error}, str::SplitWhitespace};

use TeoriaDosGrafos::{bellmanford, grafo::Grafo};


#[inline(always)]
fn decide(func : &str, grafo : &mut Grafo, parts : &mut SplitWhitespace){
    match func {
        "N" => {
            let id  = parts.next().unwrap().trim().parse().expect("Erro ao converter ID do verticie");
            let qnt_aresta =  parts.next().unwrap().trim().parse().expect("Erro ao converter qnt arestas");
            grafo.adicionar_verticie(id, qnt_aresta);
        }
        "E" => {
            let id  = parts.next().unwrap().trim().parse().expect("Erro ao converter ID do verticie de destino");
            let id_fim  = parts.next().unwrap().trim().parse().expect("Erro ao converter ID do verticie de fim");
            let custo  = parts.next().unwrap().trim().parse().expect("Erro ao converter custo");
            grafo.adicionar_aresta_verticie(id, id_fim, custo);
        }
        _ => {
        }
    }
}


fn get_grafo(path : &str) -> Result<Grafo, Error>{

    let arq = std::fs::File::open(path)?;
    let reader = std::io::BufReader::new(arq);

    let mut grafo = Grafo::new(200);

    for line in reader.lines(){
        let line = line?;
        let mut parts = line.trim().split_whitespace();

        let func = parts.next().unwrap();

        decide(func, &mut grafo, &mut parts);
    }
    Ok(grafo)
}




fn main() {
    let args : Vec<String> = std::env::args().collect();
    let path = args[1].as_str();
    let verticie = args[2].trim().parse().expect("Falta o verticie de destino");

    let g = get_grafo(&path);
    match g {
        Ok(grafo) => {
            let cam = bellmanford::bellmanford(verticie, &grafo);
            match cam{
                Some(caminhos) => {
                    for i in caminhos{
                        println!("{}", i);
                    }
                }
                None => {
                    println!("C");
                }
            }
        }
        Err(e) => {
            println!("{}", e);
        }
    }
}