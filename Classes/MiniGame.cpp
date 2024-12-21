#include "MiniGame.h"

int myFlag = 2;
int enemyFlag = 1;

const int max_important_positions = 10;  // ÿ�������ĵ�ĸ���
const int searching_depth = 6;

static Nude A;

GobangScene* GobangScene::create()
{
    GobangScene* scene = new GobangScene;
    if (scene) {
        if (scene->init()) {
            return scene;
        }
    }
    return nullptr;
}

bool GobangScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//���д����ȡ��ǰ��Ϸ��ͼ���ڵ�ԭ������

    auto board_layer = Sprite::create("MiniGameScene/Gobang_scene.png");
    board_layer->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(board_layer);

    //�˳���ť
    auto closeItem = MenuItemImage::create(
            "MiniGameScene/close_buttom.png",
            "MiniGameScene/close_buttom2.png",
        CC_CALLBACK_1(GobangScene::close, this));
    closeItem->setScale(0.5);
    float xx = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float yy = origin.y + visibleSize.height - closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(xx, yy));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(GobangScene::on_mouse_up, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
    // init board 
    my_player = new Player(A);
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            A.board[x][y] = 0;
        }
    }
    const int BOARD_MIDDLE_1 = (BOARD_SIZE + 1) / 2 - 1;
    const int BOARD_MIDDLE_2 = BOARD_SIZE / 2;
    A.board[BOARD_MIDDLE_1][BOARD_MIDDLE_1] = WHITE;
    A.board[BOARD_MIDDLE_2][BOARD_MIDDLE_2] = WHITE;
    A.board[BOARD_MIDDLE_2][BOARD_MIDDLE_1] = BLACK;
    A.board[BOARD_MIDDLE_1][BOARD_MIDDLE_2] = BLACK;

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (A.board[x][y] == myFlag) {
                auto white_piece = Sprite::create("MiniGameScene/white_piece.png");
                coordinate co = { x, y };
                white_piece->setPosition(transfer_cell_to_vision(co));
                this->addChild(white_piece);
            } 
            else if (A.board[x][y] == enemyFlag) {
                auto black_piece = Sprite::create("MiniGameScene/black_piece.png");
                coordinate co = { x, y };
                black_piece->setPosition(transfer_cell_to_vision(co));
                this->addChild(black_piece);
            }
            else {

            }
        }
    }

    return true;
}

void GobangScene::close(Ref* obj)
{
    Director::getInstance()->popScene();
}


coordinate GobangScene::transfer_vision_to_cell(Vec2 visible_position)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int pixel_per_cell = 55;
    coordinate coordinate_on_cell;

    //�����λ��ת��Ϊ�Ե�ͼ���½�Ϊԭ��
    coordinate_on_cell.x = int((visible_position.x - visibleSize.width / 2) / pixel_per_cell + 6);
    coordinate_on_cell.y = int((visible_position.y - visibleSize.height / 2) / pixel_per_cell + 6);

    return coordinate_on_cell;
}

Vec2 GobangScene::transfer_cell_to_vision(coordinate cell_coordinate)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��ǰ��Ϸ��ͼ���ڵĳߴ�
    int pixel_per_cell = 55;
    Vec2 position_on_board;

    position_on_board.x = (cell_coordinate.x - 5.5) * pixel_per_cell + visibleSize.width / 2;
    position_on_board.y = (-cell_coordinate.y + 5.5) * pixel_per_cell + visibleSize.height / 2;

    return position_on_board;
}

void GobangScene::on_mouse_up(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    Vec2 click_position = e->getLocation();
    auto piece_coordinate = transfer_vision_to_cell(click_position);
    if (turn_flag_) {
        // human player turn
        coordinate cell_coordinate = transfer_vision_to_cell(click_position);
        A.arr_input(cell_coordinate.x, cell_coordinate.y, enemyFlag);
        auto place = transfer_cell_to_vision(cell_coordinate);
        auto black_piece = Sprite::create("MiniGameScene/black_piece.png");
        black_piece->setPosition(place);
        this->addChild(black_piece);


        
        // program player turn
        turn_flag_ = 0;
        coordinate now_best_coordinate;
        my_player->evaluate_score();
        my_player->best(now_best_coordinate.x, now_best_coordinate.y);
        A.arr_input(now_best_coordinate.x, now_best_coordinate.y, myFlag);

        place = transfer_cell_to_vision(now_best_coordinate);
        auto white_piece = Sprite::create("MiniGameScene/white_piece.png");
        white_piece->setPosition(place);
        this->addChild(white_piece);

        turn_flag_ = 1;
    }
}


/**********************************************************************
*                       follewed by player
**********************************************************************/

bool judgeInRange(coordinate temp) {//�ж�λ���Ƿ񳬳�����
    if (temp.x < 0)return false;
    if (temp.y < 0)return false;
    if (temp.x >= 12)return false;
    if (temp.y >= 12)return false;
    return true;
}

int getColor(coordinate target) {//��ȡ��λ�õ���������
    return A.board[target.x][target.y];
}
void place(coordinate target) {//�����Լ�������
    A.board[target.x][target.y] = myFlag;
}



void clear(int board[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
}


Player::Player(Nude& init_board)
{
    my_nude_ = &init_board;
}

/**
 * @return ��
 */
void Player::evaluate_score()
{
    clear(score_board_);
    clear(my_score_board_);
    clear(enermy_score_board_);
    clear(importance_board_);

    this->evaluate_side_score(my_score_board_, 0);
    this->evaluate_side_score(enermy_score_board_, 1);

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            score_board_[i][j] = my_score_board_[i][j] - enermy_score_board_[i][j];
            importance_board_[i][j] = my_score_board_[i][j] + enermy_score_board_[i][j];
        }
    }
}


/**
 * @param side_score_board Ҫ������һ���ļƷ���
 * @param side 0�����ҷ���1����Է�
 */
int Player::evaluate_side_score(int side_score_board[BOARD_SIZE][BOARD_SIZE], int side)
{
    int flag = myFlag;
    if (side) {
        flag = 3 - flag;
    }

    const int piece_magnification = 10;   // ���������ʣ�ÿ������10Ϊ��������
    const double defensive_magnification = 1.0 / 3;   // �������׵ķ�����3
    const double sleepy_magnification = 1.0 / 2;
    int delta[4][2] = { {0, 1}, {1, 1}, {1, 0}, {1, -1} };
    coordinate temp_coordinate;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (my_nude_->board[i][j] == EMPTY)
                for (int direction = 0; direction < 4; direction++) {   // һ���ĸ�����
                    int score_of_line = 1;
                    int count = 0;  // �������ӣ�������һ�������
                    int sleepy = 0; // ����
                    for (int positive_flag = 0; positive_flag < 2; positive_flag++) { // һ�����ϵ��������������ң�
                        temp_coordinate.x = i;
                        temp_coordinate.y = j;
                        for (int wide = 0; wide <= 5; wide++) {
                            temp_coordinate.x += (positive_flag == 0 ? 1 : -1) * delta[direction][0], temp_coordinate.y += (positive_flag == 0 ? 1 : -1) * delta[direction][1];
                            if (judgeInRange(temp_coordinate) && getColor(temp_coordinate) == flag) {
                                count++;
                            }
                            else {
                                if (!judgeInRange(temp_coordinate) || getColor(temp_coordinate) != EMPTY) { // ����
                                    sleepy++;
                                }
                                break;
                            }
                        }
                    }
                    for (int t = 0; t < count; t++) {
                        score_of_line *= piece_magnification;
                    }
                    if (sleepy == 2) {  // ���Ҷ�������
                        if (count < 4)  // xoo+oox ��Ӯ�����౻����ʧȥ����
                            score_of_line = 0;
                    }
                    else if (sleepy == 1) {    // �������ȼ����ڻ����������ڶ���Ļ���
                        score_of_line *= sleepy_magnification;
                    }
                    if (side && count) {    // �Է��Ǻ�����
                        score_of_line *= defensive_magnification;
                    }

                    side_score_board[i][j] += score_of_line;
                }

    return 0;
}

void Player::best(int& x, int& y)
{
    // version 3.0
    int highest_score = _INF;
    this->gaming(searching_depth, highest_score, 1);
    x = target_coordinate_.x, y = target_coordinate_.y;
}

/**
 * @param max_depth ������ȣ����Ϊ0ʱ���ص�ǰ״̬����������Ϊ�������
 * @param upper_max_score ��һ���Է�˼��ʱ��һ������߷֣����Ǽ�����һ������߷ֵͣ�ֱ�Ӽ�֦
 * @param first 1��ʾ�ǵ�ǰ���Ƶ���һ����Ĭ��Ϊ0����ʾ�ò����������֧
 * @return ��·�����������
 */
int Player::gaming(int max_depth, int upper_max_score, int first = 0)
{
    this->evaluate_score();
    coordinate temp_coordinate;
    int score = 0;
    if (max_depth == 0) {
        // ������ǰ���Ʒ֣��ҷ����Ų��÷�-�Է����Ų��÷�
        int local_max_score = _INF, local_min_score = INF;
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int column = 0; column < BOARD_SIZE; column++) {
                if (score_board_[row][column] > local_max_score) {
                    local_max_score = score_board_[row][column];
                }
                if (score_board_[row][column] < local_min_score) {
                    local_min_score = score_board_[row][column];
                }
            }
        }
        score = local_max_score + local_min_score;
    }
    else {
        const int threshold = 2000; // ��Ӯ��ֵ 
        int over_threshold = 0; // �Ƿ�Խ����Ӯ��ֵ
        coordinate important_coordinates[max_important_positions + 1];    // ���һλ�����壬����Խ��
        for (int row = 0; row < BOARD_SIZE && !over_threshold; row++) {
            for (int column = 0; column < BOARD_SIZE && !over_threshold; column++) {
                if (my_nude_->board[row][column] == EMPTY) {
                    if (my_score_board_[row][column] >= threshold) {
                        over_threshold = 1;
                        score = INF - 1;
                        if (first) {
                            target_coordinate_.x = row, target_coordinate_.y = column;
                        }
                    }
                    if (!over_threshold) {
                        for (int importance_rank = max_important_positions - 1; importance_rank >= 0; importance_rank--) {
                            temp_coordinate = important_coordinates[importance_rank];
                            if (importance_board_[row][column] > importance_board_[temp_coordinate.x][temp_coordinate.y]) {
                                important_coordinates[importance_rank].x = row, important_coordinates[importance_rank].y = column;
                                important_coordinates[importance_rank + 1] = temp_coordinate;
                            }
                        }
                    }
                }
            }
        }
        if (!over_threshold) {
            int local_score;    // ��һ���������еķ���
            int local_max_score = _INF;  // ��ǰ�����
            for (int importance_rank = 0; importance_rank < max_important_positions && judgeInRange(important_coordinates[importance_rank]); importance_rank++) {
                temp_coordinate = important_coordinates[importance_rank];
                int row = temp_coordinate.x, column = temp_coordinate.y;
                if (judgeInRange(temp_coordinate)) {  // important_coordinate�Ƿǿյ�
                    my_nude_->arr_input(row, column, myFlag);
                    myFlag = enemyFlag; // ��λ˼��
                    enemyFlag = 3 - enemyFlag; // ��λ˼��
                    local_score = -this->gaming(max_depth - 1, local_max_score);
                    myFlag = enemyFlag; // ������
                    enemyFlag = 3 - enemyFlag; // ������
                    my_nude_->arr_input(row, column, EMPTY);
                    if (-local_score < upper_max_score) {
                        local_max_score = INF;
                        break;
                    }
                    if (local_score > local_max_score) {
                        local_max_score = local_score;
                        if (first) {
                            target_coordinate_.x = row, target_coordinate_.y = column;
                        }
                    }
                }
            }
            score = local_max_score;
        }
    }
    return score;
}