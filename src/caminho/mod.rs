use std::fmt:: Display;



pub struct Caminho{
    inicio : u32,
    fim    : u32,
    verticies : Vec<u32>,
    custo : i32
}


impl Caminho {
    pub fn new(inicio : u32, fim : u32) -> Self{
        Self{   
            inicio : inicio,
            fim : fim,
            verticies : Vec::with_capacity(20),
            custo : 0
        }
    }

    pub fn add_verticie(&mut self, verticie : u32){
        self.verticies.push(verticie);
    }

    pub fn set_custo(&mut self, custo : i32){
        self.custo = custo
    }

    pub fn pronto(&mut self){
        self.verticies.reverse();
    }
}


impl Display for Caminho{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {

        if self.fim == self.inicio{
            write!(f, "P {} 0 1 {}", self.inicio, self.inicio)?;
            return Ok(());
        }

        if self.verticies.len() == 0{
            write!(f, "U {}", self.fim)?;
            return Ok(());
        }
        
        write!(f, "P ")?;
        write!(f, "{} ", self.fim)?;
        write!(f, "{} ", self.custo)?;
        write!(f, "{} ", self.verticies.len() + 1)?;
        for i in &self.verticies{
            write!(f, "{} ", i)?;
        }
        write!(f, "{}", self.fim)?;
        Ok(())
    }
}