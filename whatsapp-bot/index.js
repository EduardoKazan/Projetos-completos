// index.js

  require('dotenv').config();

  const { Client, LocalAuth } = require('whatsapp-web.js');
  const qrcode = require('qrcode-terminal');
  const { OpenAI } = require('openai');

  // Configurar OpenAI/Deepseek
  const openai = new OpenAI({
    apiKey: process.env.OPENAI_API_KEY,
  });

  // Inicializa cliente WhatsApp
  const client = new Client({
    authStrategy: new LocalAuth(),
    puppeteer: { headless: true }
  });

  client.on('qr', qr => {
    qrcode.generate(qr, { small: true });
    console.log('Escaneie o QR code para logar no WhatsApp');
  });

  client.on('ready', () => {
    console.log('Cliente está pronto!');
  });

  client.on('message', async msg => {
    // Ignore mensagens de grupos (opcional)
    // if (msg.from.endsWith('@g.us')) return;
    try {
      if (msg.body.startsWith('!ask ')) {
        const prompt = msg.body.replace('!ask ', '');

        // Pede resposta ao modelo da OpenAI (ou DeepSeek)
        const response = await openai.chat.completions.create({
          model: "gpt-3.5-turbo", // ou outro modelo, verifique sua API
          messages: [{ role: "user", content: prompt }],
        });

        // Envia resposta para o WhatsApp
        const answer = response.choices && response.choices[0]?.message?.content;
        await msg.reply(answer || 'Desculpe, não consegui uma resposta.');
      }
    } catch (err) {
      console.error('Erro:', err);
      await msg.reply('Erro ao consultar a IA.');
    }
  });

  client.initialize();