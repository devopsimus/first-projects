import telebot
import config
import random

from telebot import types

bot = telebot.TeleBot("1104485640:AAFj-xyHCKk2NN2j6FkUkffwkTWXFnkwX5M")

@bot.message_handler(commands=['start'])
def welcome(message):
    sticker = open('D:/Projects/Stickers/pp.jpg', 'rb')
    bot.send_sticker(message.chat.id, sticker)
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    item1 = types.KeyboardButton('Button1-Type1')
    item2 = types.KeyboardButton('Button2-Type1')
    markup.add(item1, item2)
    bot.send_message(message.chat.id, "Welcome, {0.first_name}!\nI - <b>{1.first_name}</b>, and we are - {1.first_name}".format(message.from_user, bot.get_me()),
    parse_mode='html', reply_markup=markup)
 
@bot.message_handler(content_types=['text'])
def lalala(message):
    if message.chat.type == 'private':
        if message.text == 'Button1-Type1':
            bot.send_message(message.chat.id, "Error")
        elif message.text == 'Button1-Type1':
 
            markup = types.InlineKeyboardMarkup(row_width=2)
            item1 = types.InlineKeyboardButton("Button1", callback_data='but1')
            item2 = types.InlineKeyboardButton("Button2", callback_data='but2')
            item3 = types.InlineKeyboardButton("Button3", callback_data='but3')
            item4 = types.InlineKeyboardButton("Button4", callback_data='but4')
 
            markup.add(item1, item2, item3, item4)
 
            bot.send_message(message.chat.id, 'Push the button', reply_markup=markup)
        else:
            bot.send_message(message.chat.id, '404 Error!')
 
@bot.callback_query_handler(func=lambda call: True)
def callback_inline(call):
    try:
        if call.message:
            if call.data == 'but1':
                photo1 = open('D:/File-Path', 'rb')
                bot.send_photo(call.message.chat.id, photo1)
                bot.send_message(call.message.chat.id, 'Button')
            elif call.data == 'but2':
                photo2 = open('D:/File-Path', 'rb')
                bot.send_photo(call.message.chat.id, photo2)
                bot.send_message(call.message.chat.id, 'Button')
            elif call.data == 'but3':
                photo3 = open('D:/File-Path', 'rb')
                bot.send_photo(call.message.chat.id, photo3)
                bot.send_message(call.message.chat.id, 'Button')
            elif call.data == 'but4':
                photo4 = open('D:/File-Path', 'rb')
                bot.send_photo(call.message.chat.id, photo4)
                bot.send_message(call.message.chat.id, 'Button')
 
            # remove inline buttons
            bot.edit_message_text(chat_id=call.message.chat.id, message_id=call.message.message_id, text="Deleting old staff",
                reply_markup=None)
 
            # show alert
            bot.answer_callback_query(callback_query_id=call.id, show_alert=False,
                text="Test only!")
 
    except Exception as e:
        print(repr(e))
 
# RUN
bot.polling(none_stop=True)
