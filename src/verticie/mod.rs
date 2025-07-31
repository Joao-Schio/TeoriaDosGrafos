
use crate::aresta::Aresta;


#[derive(Debug)]
pub struct Verticie{
    id : u32,
    arestas : Vec<Aresta>
}



impl Verticie{

    pub fn new(id : u32, qnt_aresta : usize) -> Self{
        Self { id: id, arestas: Vec::with_capacity(qnt_aresta) }
    }


    #[inline(always)]
    pub fn add_aresta(&mut self, destino : u32, custo : i32){
        self.arestas.push(
            Aresta::new(destino, custo)
        );
    }
    #[inline(always)]
    pub fn get_id(&self) -> u32{
        self.id
    }

    pub fn get_arestas(&self) -> &[Aresta]{
        &self.arestas
    }
}
