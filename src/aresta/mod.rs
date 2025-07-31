



#[derive(Debug)]
pub struct Aresta{
    destino : u32,
    custo   : i32
}



impl Aresta{
    pub fn new(destino : u32, custo : i32) -> Self{
        Self { destino: destino, custo: custo }
    }

    #[inline(always)]
    pub fn get_destino(&self) -> u32{
        self.destino
    }

    #[inline(always)]
    pub fn get_custo(&self) -> i32{
        self.custo
    }
}