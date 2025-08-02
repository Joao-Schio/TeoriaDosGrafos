
use std::i32;

use crate::{caminho::Caminho, grafo::Grafo};

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Ant{
    Tem(usize),
    NaoTem
}

#[inline(always)]
fn print_vec<T : std::fmt::Display>(vet : &[T], num_it : usize){
    print!("O {} ", num_it);
    for i in &vet[0..vet.len() - 1]{
        print!("{} ", i);
    }
    println!("{}", vet[vet.len() - 1]);
}

fn desmarcar(vet : &mut Vec<bool>){
    for i in vet{
        *i = false;
    }
}

fn ciclo_neg(grafo : &Grafo, custos : &[i32]) -> bool{
    for i in 0..grafo.get_tamanho(){
        let v = grafo.get_verticies(i as u32);
        for a in v.get_arestas(){
            let dest = a.get_destino();
            let custo = a.get_custo();
            if custos[dest as usize] > custos[v.get_id() as usize] + custo{
                return true;
            }
        }
    }
    false
}

pub fn bellmanford(verticie : u32, grafo : &Grafo) -> Option<Vec<Caminho>>{
    let tamanho_grafo = grafo.get_tamanho();

    let mut saida = Vec::with_capacity(tamanho_grafo);

    let mut custos = vec![i32::MAX / 16 ; tamanho_grafo];
    let mut anterior = vec![Ant::NaoTem; tamanho_grafo];

    let mut ordem : Vec<u32> = (0..tamanho_grafo as u32).collect();
    let mut visitados = vec![false ; tamanho_grafo];
    let mut reduzidos = vec![false; tamanho_grafo];
    let mut reduzidosApos = vec![false; tamanho_grafo];
    let mut inseridos = vec![false; tamanho_grafo];
    ordem.swap(verticie as usize, 0);
    ordem[1..].sort();
    
    custos[verticie as usize] = 0;
    let mut count = 0;
    loop{
        if count == tamanho_grafo{
            break;
        }
        
        print_vec(&ordem, count);
        desmarcar(&mut visitados);
        desmarcar(&mut reduzidos);
        desmarcar(&mut reduzidosApos);
        desmarcar(&mut inseridos);
        let mut entrouRedApos = false;
        let mut entrouRed = false;

        for i in &ordem{
            let u = grafo.get_verticies(*i);
            visitados[*i as usize] = true;
            for a in u.get_arestas(){
                let id_dest = a.get_destino();
                let custo = a.get_custo();
                if custos[id_dest as usize] > custos[*i as usize] + custo{
                    custos[id_dest as usize] = custos[*i as usize] + custo;
                    anterior[id_dest as usize] = Ant::Tem(*i as usize);
                    if visitados[id_dest as usize]{
                        reduzidosApos[id_dest as usize] = true;
                        entrouRedApos = true;
                    }
                    else if !visitados[id_dest as usize]{
                        reduzidos[id_dest as usize] = true;
                        entrouRed = true;
                    }
                }
            }
        }
        if !entrouRed && !entrouRedApos{
            for i in (count + 1)..tamanho_grafo{
                print_vec(&ordem, i);
            }
            break;
        }

        let mut prox = Vec::with_capacity(tamanho_grafo);

        for i in &ordem{
            if reduzidosApos[*i as usize]{
                prox.push(*i);
                inseridos[*i as usize] = true;
            }
        }

        for i in &ordem{
            if reduzidos[*i as usize] && ! inseridos[*i as usize]{
                prox.push(*i);
                inseridos[*i as usize] = true;
            }
        }

        for i in &ordem{
            if !inseridos[*i as usize]{
                prox.push(*i);
            }
        }
        ordem = prox;
        count += 1
    }   

    if ciclo_neg(grafo, &custos){
        return None;
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
        cam.set_custo(custos[i]);
        cam.pronto();
        saida.push(cam);
    }
    Some(saida)
}