# Boot Loader feito em C

<p>Esses arquivos são para um bootloader feito em C. O objetivo era mostrar que sim, é possível criar um bootloader em C.</p>

<p>O 'truque' é usar um ldscript para stripar o código removendo quaisquer informações e colocar todas as seções começando logo após 0x7C00.</p>

<p>Uma seção também é criada para iniciar em 0x7DFE deixando 2 bytes disponívels para incluir a assinatura de boot AA55</p>

<p>Uma vez que conseguimos gerar esse binário puro e já com a assinatura de boot e contendo EXATAMENTE 512 bytes, podemos codificar em C, embora seja necessário e/ou útil usar bastante asminline para </p>

<p>A pasta boot-com-gcc-as-ld-objcopy tem exemplos graduais e os arquivos possuem comentários úteis e referências</p> 

<p>Esse código foi criado em 2014, estou deixando no github apenas como legado</p>
