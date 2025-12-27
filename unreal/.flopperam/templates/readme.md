# Flopperam Templates voor Superfamily

Dit zijn Blueprint templates die Flopperam kan gebruiken om snel game elementen te genereren.

## Beschikbare Templates

### Level Templates
- `L_Template_Standard` - Basis 2.5D platformer level
- `L_Template_Boss` - Boss encounter level

### Actor Templates

#### Gameplay
- `BP_Platform_Static` - Statisch platform
- `BP_Platform_Moving` - Bewegend platform (oscillerend)
- `BP_Platform_Falling` - Vallend platform (na aanraking)
- `BP_Collectible_Coin` - Verzamelbare munt
- `BP_Collectible_Star` - Ster collectible
- `BP_Checkpoint` - Checkpoint voor respawn

#### Education
- `BP_QuestionTrigger_Standard` - Standaard vraag trigger
- `BP_QuestionTrigger_Door` - Blokkerende vraag deur
- `BP_QuestionTrigger_Boss` - Boss vraag sequentie

#### Environment
- `BP_Decoration_Tree` - Decoratieve boom
- `BP_Decoration_Bush` - Decoratieve struik
- `BP_Decoration_Rock` - Decoratieve rots

## Flopperam Commando's

### Level Generatie
```
flopperam create level "Forest Level 3" --template Standard --length 5000 --difficulty Groep2
```

### Actor Plaatsing
```
flopperam place "Coin Arc" --count 10 --start 0,0,100 --end 500,0,300
flopperam place "Question Door" --position 1500,0,0 --subject Rekenen
flopperam place "Moving Platform" --start 2000,0,200 --end 2500,0,200 --period 3
```

### Batch Operaties
```
flopperam batch populate-level "L_W01_Level05" --coins 20 --questions 3 --platforms auto
```

## Status

**Let op**: Flopperam is momenteel in beta. Meld je aan op https://flopperam.com/beta voor toegang.

De configuratie in `.flopperam/config.json` bevat placeholder waarden. Vervang `${FLOPPERAM_API_KEY}` met je echte API key na registratie.
