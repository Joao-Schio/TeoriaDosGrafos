
use crate::verticie::Verticie;


#[derive(Debug)]
pub struct Grafo{
    verticies : Vec<Verticie>
}


impl Grafo{

    pub fn new(qnt_verticie : usize) -> Self{
        Self { verticies: Vec::with_capacity(qnt_verticie) }
    }


    pub fn adicionar_verticie(&mut self, id : u32, qnt_aresta : usize) {
        self.verticies.push(
            Verticie::new(
                id, 
                qnt_aresta
            )
        );
        self.verticies.sort_by(|v1, v2| v1.get_id().cmp(&v2.get_id()));
    }

    pub fn adicionar_aresta_verticie(&mut self, id_origem : u32, id_destino : u32, custo : i32){
        let v = self.verticies.iter_mut().find(|v| v.get_id() == id_origem).expect("Verticie inexistente");
        v.add_aresta(id_destino, custo);
    }

    #[inline(always)]
    pub fn get_tamanho(&self) -> usize{
        self.verticies.len()
    }

    pub fn get_verticies(&self, id : u32) -> &Verticie{
        match self.verticies.binary_search_by_key(&id, |v| v.get_id()) {
            Ok(index) => &self.verticies[index],
            Err(_) => panic!("Verticie com id {} não encontrado", id),
        }
    }
}