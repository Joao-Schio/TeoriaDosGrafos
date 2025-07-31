
use std::i32;

use crate::{caminho::Caminho, grafo::Grafo};

#[derive(Clone, Copy, PartialEq, Eq)]
enum Ant{
    Tem(usize),
    NaoTem
}

fn print_vec<T : std::fmt::Display>(vet : &Vec<T>){
    for i in vet{
        print!("{} ", i);
    }
    println!();
}


pub fn bellmanford(verticie : u32, grafo : &Grafo) -> Vec<Caminho>{
    let tamanho_grafo = grafo.get_tamanho();

    let mut saida = Vec::with_capacity(tamanho_grafo);

    let mut custos = vec![i32::MAX ; tamanho_grafo];
    let mut anterior = vec![Ant::NaoTem; tamanho_grafo];

    let mut ordem : Vec<u32> = (0..tamanho_grafo as u32).collect();
    let mut visitados = vec![false ; tamanho_grafo];
    let mut reduzidos = vec![false; tamanho_grafo];
    ordem.swap(verticie as usize, 0);
    ordem[1..].sort();
    
    custos[verticie as usize] = 0;
    let mut count = 0;
    loop{
        print_vec(&ordem);
        visitados.fill(false);
        let mut prox : Vec<u32>  = Vec::with_capacity(tamanho_grafo);
        let mut melhorou = false;
        for verticie in &ordem{
            let u = grafo.get_verticies(*verticie);
            let u_id  = u.get_id() as usize;
            visitados[u_id]  = true;
            for aresta in u.get_arestas(){
                let v = aresta.get_destino() as usize;
                if custos[u_id] + aresta.get_custo() < custos[v]{
                    custos[v] = custos[u_id] + aresta.get_custo();
                    anterior[v] = Ant::Tem(u_id);
                    reduzidos[v] = true;
                    if !visitados[v]{
                        prox.push(v as u32);
                    }
                    melhorou = true;
                }
            }
        }
        for &v_id in &ordem {
            let v = v_id as usize;
            if !reduzidos[v] && !prox.contains(&v_id) {
                prox.push(v_id)
            }
        }
        ordem = prox;

        if count < tamanho_grafo - 1 && !melhorou || count == tamanho_grafo - 1{
            break;
        }
        count += 1;
    }   

    for i in 0..tamanho_grafo{
        let mut cam = Caminho::new(verticie, i as u32);
        let mut x = anterior[i];
        loop{
            match &x {
                Ant::NaoTem => {
                    break;
                }
                Ant::Tem(some) => {
                    cam.add_verticie(*some as u32);
                    x = anterior[*some];
                }
            }
        }
        saida.push(cam);
    }
    saida
}